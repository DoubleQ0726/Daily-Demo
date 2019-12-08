#include "Huffman.h"



Huffman::Huffman()
{
	Init();
}


Huffman::~Huffman()
{
	delete[] code;
}

void Huffman::ComputeFrequency(string fileName)//计算每个字符出现的频率
{
	ifstream textFile;
	textFile.open(fileName.c_str());
	if (!textFile.is_open())
	{
		cout << "Cannot Open The File!" << endl;
		exit(0);
	}
	char ch;
	while (ch = textFile.get(), !textFile.eof())//这里要注意这个写法比较合理
	{
		frequencyMap[ch] += 1;
	}
	textFile.close();
}

void Huffman::ChooseMinNodes(int n, int &pos_one, int &pos_two)//从节点中找出最小的两个数的位置
{
	int64_t min1 = 9999999999;
	int64_t min2 = 9999999999;
	int tempPos1 = 0;//用来记录位置
	int tempPos2 = 0;
	for (size_t i = 0; i < n; i++)
	{
		if (nodeList[i].parent != 0)//表示这个节点已经被放入Huffman树了
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
	//根据哈夫曼树的性质，总结点数num = 2n-1
	size_t i;
	int parent;
	num = 2 * frequencyMap.size() - 1;
	int start;
	map<char, int64_t>::iterator iter = frequencyMap.begin();
	for (i = 0; i < frequencyMap.size(), iter != frequencyMap.end(); i++)//初始化所有叶子节点
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
	for (; i < num; i++)//初始化多余的构造节点
	{
		Node node;
		node.ch = NULL;
		node.parent = 0;
		node.weight = 0;
		node.lChild = 0;
		node.rChild = 0;
		nodeList.push_back(node);
	}
	for (i = frequencyMap.size(); i < num; i++)//循环构建哈夫曼树
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
	int n = frequencyMap.size();//对每个字符进行Hufman 0 1编码
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
		strcpy_s(code[i], n - start, &ch[start]);//从某个位置开始之后的几个字符复制过去
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
				tempCode.binaryCode <<= 1;//左移一位赋值
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
		if (tempUnit.remain == tempCode.length)//若单元中剩余位置大小等于code长度
		{
			tempUnit.content <<= tempCode.length;
			tempUnit.content |= tempCode.binaryCode;
			writeFp.write((char*)(&tempUnit.content), sizeof(tempUnit.content));  //将单元整个写入
			//写入之后没有剩余位置，所以要重新初始化
			tempUnit.remain = 64;//初始化该单元
			tempUnit.content = 0;
		}
		else if (tempUnit.remain > tempCode.length)//若单元中剩余位置大小大于code长度，将code放入单元中
		{
			tempUnit.content <<= tempCode.length;
			tempUnit.content |= tempCode.binaryCode;
			tempUnit.remain = tempUnit.remain - tempCode.length;
		}
		else//若单元中剩余位置大小小于code长度，将部分code放入单元，则要先将部分code写入单元，再将单元写入文件后，将其余code写入单元
		{
			__int64 temp = 0;
			tempUnit.content <<= tempUnit.remain;
			temp = tempCode.binaryCode >> (tempCode.length - tempUnit.remain);
			tempUnit.content |= temp;
			writeFp.write((char*)(&tempUnit.content), sizeof(tempUnit.content));
			//二进制移位操作的魅力
			tempUnit.content = 0;
			temp = 0xFFFFFFFFFFFFFFFF;
			temp <<= (tempCode.length - tempUnit.remain);
			temp = ~temp;//求反
			temp &= tempCode.binaryCode;//11的时候只有&才能为其本身  即11&10=10
			tempUnit.content |= temp;//00的时候只有|才能为其本身  即00|10 =10
			tempUnit.remain = 64 - (tempCode.length - tempUnit.remain);
		}
	}
	if (tempUnit.remain != 64) //当一个单元没有被写入，将剩余的写入
	{
		//FIXME:这样会导致多写入0，那么如果有哈弗曼编码位00..,就会出错
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
		readFp.read((char*)(&temp2), sizeof(__int64));//每次循环都读出一块单元进行解码
		if (readFp.fail())
		{
			break;
		}
		for (size_t i = 0; i < 64; i++)//根据得到的0,1从根节点往下，直到叶子节点输出相应字符
		{
			temp = temp2 & one;
			if (temp == 0)
			{
				child = nodeList[num].lChild;//这里num不能减一，对于根节点没问题，但对于其中的子节点会出错(因此采用了一开始的num就是总结点数 - 2)
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



