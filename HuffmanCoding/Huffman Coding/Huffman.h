#pragma once
#include <fstream>
#include <string>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

struct Node//Huffman���Ľڵ�
{
	int64_t weight;//�ڵ��Ȩֵ
	int parent;
	int lChild;
	int rChild;
	char ch;
};

struct  BinaryCode
{
	__int64 binaryCode;//����������Ķ����Ʊ�ʾ����
	int length;//���볤��
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
	void GetBinaryCode();//���Ѿ������õı����ö����Ʊ�ʾ��ͳһ���ַ���Ӧ���Ա�洢ʱ����ת��
	void WriteFile(string rfileName, string wfileName);
	void Init();//��ʼ��ÿ����Ԫ
	void Decode(string wfileName);//����

public:
	int num;//�ڵ�����
	map<char, int64_t> frequencyMap;
	vector<Node> nodeList;
	char **code;//�洢Huffman����
	map<char, BinaryCode> codeMap;
	Unit tempUnit;
};

