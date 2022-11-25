#include "Morphing.h"

#define	VALUE_MOVE_MODEL	(0.50f)					// 移動速度
#define	RATE_MOVE_MODEL		(0.20f)					// 移動慣性係数
#define	VALUE_ROTATE_MODEL	(XM_PI * 0.05f)			// 回転速度
#define	RATE_ROTATE_MODEL	(0.20f)					// 回転慣性係数
#define	SCALE_MODEL			(10.0f)					// 回転慣性係数

void Morphing::LoadModel(char * FileName, MODEL * Model)
{
	XMFLOAT3	*positionArray;
	XMFLOAT3	*normalArray;
	XMFLOAT2	*texcoordArray;

	unsigned short	positionNum = 0;
	unsigned short	normalNum = 0;
	unsigned short	texcoordNum = 0;
	unsigned short	vertexNum = 0;
	unsigned short	indexNum = 0;
	unsigned short	in = 0;
	unsigned short	subsetNum = 0;

	MODEL_MATERIAL	*materialArray = NULL;
	unsigned short	materialNum = 0;

	char str[256];
	char *s;
	char c;


	FILE *file;
	file = fopen(FileName, "rt");
	if (file == NULL)
	{
		printf("エラー:LoadModel %s \n", FileName);
		return;
	}



	//要素数カウント
	while (TRUE)
	{
		fscanf(file, "%s", str);

		if (feof(file) != 0)
			break;

		if (strcmp(str, "v") == 0)
		{
			positionNum++;
		}
		else if (strcmp(str, "vn") == 0)
		{
			normalNum++;
		}
		else if (strcmp(str, "vt") == 0)
		{
			texcoordNum++;
		}
		else if (strcmp(str, "usemtl") == 0)
		{
			subsetNum++;
		}
		else if (strcmp(str, "f") == 0)
		{
			in = 0;

			do
			{
				fscanf(file, "%s", str);
				vertexNum++;
				in++;
				c = fgetc(file);
			} while (c != '\n' && c != '\r');

			//四角は三角に分割
			if (in == 4)
				in = 6;

			indexNum += in;
		}
	}


	//メモリ確保
	positionArray = new XMFLOAT3[positionNum];
	normalArray = new XMFLOAT3[normalNum];
	texcoordArray = new XMFLOAT2[texcoordNum];


	Model->VertexArray = new VERTEX_3D[vertexNum];
	Model->VertexNum = vertexNum;

	Model->IndexArray = new unsigned short[indexNum];
	Model->IndexNum = indexNum;

	Model->SubsetArray = new SUBSET[subsetNum];
	Model->SubsetNum = subsetNum;




	//要素読込
	XMFLOAT3 *position = positionArray;
	XMFLOAT3 *normal = normalArray;
	XMFLOAT2 *texcoord = texcoordArray;

	unsigned short vc = 0;
	unsigned short ic = 0;
	unsigned short sc = 0;


	fseek(file, 0, SEEK_SET);

	while (TRUE)
	{
		fscanf(file, "%s", str);

		if (feof(file) != 0)
			break;

		if (strcmp(str, "mtllib") == 0)
		{
			//マテリアルファイル
			fscanf(file, "%s", str);

			char path[256];
			strcpy(path, "data/model/");
			strcat(path, str);

			LoadMaterial(path, &materialArray, &materialNum);
		}
		else if (strcmp(str, "o") == 0)
		{
			//オブジェクト名
			fscanf(file, "%s", str);
		}
		else if (strcmp(str, "v") == 0)
		{
			//頂点座標
			fscanf(file, "%f", &position->x);
			fscanf(file, "%f", &position->y);
			fscanf(file, "%f", &position->z);
			position->x *= SCALE_MODEL;
			position->y *= SCALE_MODEL;
			position->z *= SCALE_MODEL;
			position++;
		}
		else if (strcmp(str, "vn") == 0)
		{
			//法線
			fscanf(file, "%f", &normal->x);
			fscanf(file, "%f", &normal->y);
			fscanf(file, "%f", &normal->z);
			normal++;
		}
		else if (strcmp(str, "vt") == 0)
		{
			//テクスチャ座標
			fscanf(file, "%f", &texcoord->x);
			fscanf(file, "%f", &texcoord->y);
			texcoord->y = 1.0f - texcoord->y;
			texcoord++;
		}
		else if (strcmp(str, "usemtl") == 0)
		{
			//マテリアル
			fscanf(file, "%s", str);

			if (sc != 0)
				Model->SubsetArray[sc - 1].IndexNum = ic - Model->SubsetArray[sc - 1].StartIndex;

			Model->SubsetArray[sc].StartIndex = ic;


			for (unsigned short i = 0; i < materialNum; i++)
			{
				if (strcmp(str, materialArray[i].Name) == 0)
				{
					Model->SubsetArray[sc].Material.Material = materialArray[i].Material;
					strcpy(Model->SubsetArray[sc].Material.TextureName, materialArray[i].TextureName);
					strcpy(Model->SubsetArray[sc].Material.Name, materialArray[i].Name);

					break;
				}
			}

			sc++;

		}
		else if (strcmp(str, "f") == 0)
		{
			//面
			in = 0;

			do
			{
				fscanf(file, "%s", str);

				s = strtok(str, "/");
				Model->VertexArray[vc].Position = positionArray[atoi(s) - 1];
				if (s[strlen(s) + 1] != '/')
				{
					//テクスチャ座標が存在しない場合もある
					s = strtok(NULL, "/");
					Model->VertexArray[vc].TexCoord = texcoordArray[atoi(s) - 1];
				}
				s = strtok(NULL, "/");
				Model->VertexArray[vc].Normal = normalArray[atoi(s) - 1];

				Model->VertexArray[vc].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

				Model->IndexArray[ic] = vc;
				ic++;
				vc++;

				in++;
				c = fgetc(file);
			} while (c != '\n' && c != '\r');

			//四角は三角に分割
			if (in == 4)
			{
				Model->IndexArray[ic] = vc - 4;
				ic++;
				Model->IndexArray[ic] = vc - 2;
				ic++;
			}
		}
	}


	if (sc != 0)
		Model->SubsetArray[sc - 1].IndexNum = ic - Model->SubsetArray[sc - 1].StartIndex;





	delete[] positionArray;
	delete[] normalArray;
	delete[] texcoordArray;
	delete[] materialArray;

	fclose(file);

}
