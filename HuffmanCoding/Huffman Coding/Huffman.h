#pragma once
#include <fstream>
#include <string>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

struct Node//Huffman树的节点
{
	int64_t weight;//节点的权值
	int parent;
	int lChild;
	int rChild;
	char ch;
};

struct  BinaryCode
{
	__int64 binaryCode;//哈弗曼编码的二进制表示方法
	int length;//编码长度
};
struct Unit
{
	__int64 content;
	int remain;
};

class Huffman
{
public:
	Huffman();
	~Huffman();
	void ComputeFrequency(string fileName);
	void ChooseMinNodes(int n, int &pos_one, int &pos_two);
	void HuffmanCoding();
	void GetBinaryCode();//将已经构建好的编码用二进制表示并统一于字符对应，以便存储时进行转化
	void WriteFile(string rfileName, string wfileName);
	void Init();//初始化每个单元
	void Decode(string wfileName);//解码

public:
	int num;//节点总数
	map<char, int64_t> frequencyMap;
	vector<Node> nodeList;
	char **code;//存储Huffman编码
	map<char, BinaryCode> codeMap;
	Unit tempUnit;
};

