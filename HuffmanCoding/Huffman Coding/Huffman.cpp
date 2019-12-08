#include "Huffman.h"



Huffman::Huffman()
{
	Init();
}


Huffman::~Huffman()
{
	delete[] code;
}

void Huffman::ComputeFrequency(string fileName)//����ÿ���ַ����ֵ�Ƶ��
{
	ifstream textFile;
	textFile.open(fileName.c_str());
	if (!textFile.is_open())
	{
		cout << "Cannot Open The File!" << endl;
		exit(0);
	}
	char ch;
	while (ch = textFile.get(), !textFile.eof())//����Ҫע�����д���ȽϺ���
	{
		frequencyMap[ch] += 1;
	}
	textFile.close();
}

void Huffman::ChooseMinNodes(int n, int &pos_one, int &pos_two)//�ӽڵ����ҳ���С����������λ��
{
	int64_t min1 = 9999999999;
	int64_t min2 = 9999999999;
	int tempPos1 = 0;//������¼λ��
	int tempPos2 = 0;
	for (size_t i = 0; i < n; i++)
	{
		if (nodeList[i].parent != 0)//��ʾ����ڵ��Ѿ�������Huffman����
		{
			continue;
		}
		else
		{
			if (nodeList[i].weight <=  min2)
			{
				if (nodeList[i].weight <= min1)
				{
					min2 = min1;
					tempPos2 = tempPos1;
					min1 = nodeList[i].weight;
					tempPos1 = i;
				}
				else
				{
					min2 = nodeList[i].weight;
					tempPos2 = i;
				}
			}
		}
	}
	pos_one = tempPos1;
	pos_two = tempPos2;
}

void Huffman::HuffmanCoding()
{
	//���ݹ������������ʣ��ܽ����num = 2n-1
	size_t i;
	int parent;
	num = 2 * frequencyMap.size() - 1;
	int start;
	map<char, int64_t>::iterator iter = frequencyMap.begin();
	for (i = 0; i < frequencyMap.size(), iter != frequencyMap.end(); i++)//��ʼ������Ҷ�ӽڵ�
	{
		Node node;
		node.ch = iter->first;
		node.parent = 0;
		node.weight = iter->second;
		node.lChild = 0;
		node.rChild = 0;
		nodeList.push_back(node);
		iter++;
	}
	for (; i < num; i++)//��ʼ������Ĺ���ڵ�
	{
		Node node;
		node.ch = NULL;
		node.parent = 0;
		node.weight = 0;
		node.lChild = 0;
		node.rChild = 0;
		nodeList.push_back(node);
	}
	for (i = frequencyMap.size(); i < num; i++)//ѭ��������������
	{
		int pos_one;
		int pos_two;
		ChooseMinNodes(i, pos_one, pos_two);
		nodeList[pos_one].parent = i;
		nodeList[pos_two].parent = i;
		nodeList[i].lChild = pos_one;
		nodeList[i].rChild = pos_two;
		nodeList[i].weight = nodeList[pos_one].weight + nodeList[pos_two].weight;
	}
	int n = frequencyMap.size();//��ÿ���ַ�����Hufman 0 1����
	code = new char *[n + 1];
	char *ch = new char[n];
	ch[n - 1] = '\0';
	for (size_t i = 0; i < n; i++)
	{
		start = n - 1;
		for (size_t j = i, parent = nodeList[i].parent; parent != 0; j = parent, parent = nodeList[parent].parent)
		{
			if (nodeList[parent].lChild == j)
			{
				ch[--start] = '0';
			}
			else
			{
				ch[--start] = '1';
			}
		}
		code[i] = new char[n - start];
		strcpy_s(code[i], n - start, &ch[start]);//��ĳ��λ�ÿ�ʼ֮��ļ����ַ����ƹ�ȥ
	}
	delete ch;
}

void Huffman::GetBinaryCode()
{
	map<char, int64_t>::iterator iter = frequencyMap.begin();
	BinaryCode tempCode;
	__int64 one = 1;
	for (size_t i = 0; i < frequencyMap.size(); i++)
	{
		tempCode.binaryCode = 0;
		tempCode.length = 0;
		for (size_t j = 0; code[i][j] != '\0'; j++)
		{
			if (code[i][j] == '1')
			{
				tempCode.binaryCode <<= 1;//����һλ��ֵ
				tempCode.binaryCode = one | tempCode.binaryCode;
			}
			if (code[i][j] == '0')
			{
				tempCode.binaryCode <<= 1;
			}
			tempCode.length++;
		}
		codeMap[iter->first] = tempCode;
		iter++;
	}
}

void Huffman::WriteFile(string rfileName, string wfileName)
{
	fstream readFp(rfileName, ios::in);
	fstream writeFp(wfileName, ios::out | ios::binary);
	if (!readFp || !writeFp)
	{
		cout << "can not open the file!" << endl;
		exit(0);
	}
	char ch;
	BinaryCode tempCode;
	while (ch = readFp.get(), !readFp.eof())
	{
		tempCode = codeMap[ch];
		if (tempUnit.remain == tempCode.length)//����Ԫ��ʣ��λ�ô�С����code����
		{
			tempUnit.content <<= tempCode.length;
			tempUnit.content |= tempCode.binaryCode;
			writeFp.write((char*)(&tempUnit.content), sizeof(tempUnit.content));  //����Ԫ����д��
			//д��֮��û��ʣ��λ�ã�����Ҫ���³�ʼ��
			tempUnit.remain = 64;//��ʼ���õ�Ԫ
			tempUnit.content = 0;
		}
		else if (tempUnit.remain > tempCode.length)//����Ԫ��ʣ��λ�ô�С����code���ȣ���code���뵥Ԫ��
		{
			tempUnit.content <<= tempCode.length;
			tempUnit.content |= tempCode.binaryCode;
			tempUnit.remain = tempUnit.remain - tempCode.length;
		}
		else//����Ԫ��ʣ��λ�ô�СС��code���ȣ�������code���뵥Ԫ����Ҫ�Ƚ�����codeд�뵥Ԫ���ٽ���Ԫд���ļ��󣬽�����codeд�뵥Ԫ
		{
			__int64 temp = 0;
			tempUnit.content <<= tempUnit.remain;
			temp = tempCode.binaryCode >> (tempCode.length - tempUnit.remain);
			tempUnit.content |= temp;
			writeFp.write((char*)(&tempUnit.content), sizeof(tempUnit.content));
			//��������λ����������
			tempUnit.content = 0;
			temp = 0xFFFFFFFFFFFFFFFF;
			temp <<= (tempCode.length - tempUnit.remain);
			temp = ~temp;//��
			temp &= tempCode.binaryCode;//11��ʱ��ֻ��&����Ϊ�䱾��  ��11&10=10
			tempUnit.content |= temp;//00��ʱ��ֻ��|����Ϊ�䱾��  ��00|10 =10
			tempUnit.remain = 64 - (tempCode.length - tempUnit.remain);
		}
	}
	if (tempUnit.remain != 64) //��һ����Ԫû�б�д�룬��ʣ���д��
	{
		//FIXME:�����ᵼ�¶�д��0����ô����й���������λ00..,�ͻ����
		tempUnit.content <<= tempUnit.remain;
		writeFp.write((char*)(&tempUnit.content), sizeof(tempUnit.content));
	}
	readFp.close();
	writeFp.close();
	}

void Huffman::Init()
{
	tempUnit.content = 0;
	tempUnit.remain = 64;
}

void Huffman::Decode(string wfileName)
{
	int len = frequencyMap.size();
	int num = 2 * len - 2;
	int child = 0;
	fstream readFp(wfileName, ios::in | ios::binary);
	if (!readFp)
	{
		cout << "can not open the file." << endl;
		exit(0);
	}
	__int64 one = 0;
	__int64 temp = 0;
	__int64 temp2 = 0;
	one = 0x8000000000000000;//1000 0000 0000 0000
	while (!readFp.eof())
	{
		readFp.read((char*)(&temp2), sizeof(__int64));//ÿ��ѭ��������һ�鵥Ԫ���н���
		if (readFp.fail())
		{
			break;
		}
		for (size_t i = 0; i < 64; i++)//���ݵõ���0,1�Ӹ��ڵ����£�ֱ��Ҷ�ӽڵ������Ӧ�ַ�
		{
			temp = temp2 & one;
			if (temp == 0)
			{
				child = nodeList[num].lChild;//����num���ܼ�һ�����ڸ��ڵ�û���⣬���������е��ӽڵ�����(��˲�����һ��ʼ��num�����ܽ���� - 2)
			}
			else
			{
				child = nodeList[num].rChild;
			}
			num = child;
			temp2 <<= 1;
			if (nodeList[child].lChild == 0 && nodeList[child].rChild == 0)
			{
				cout << nodeList[child].ch;
				num = 2 * len - 2;
				child = 0;
			}
		}
	}
	readFp.close();
}



