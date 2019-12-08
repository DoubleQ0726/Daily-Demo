#include <iostream>
#include <iomanip>
#include "Huffman.h"
using namespace std;

int main()
{
	Huffman Hf;
	string rfileName = "E:/Temp/Huffman Coding/Huffman Coding/Aesop_Fables.txt";
	string wfileName = "E:/Temp/Huffman Coding/Huffman Coding/Aesop_Fables_compress.dat";
	Hf.ComputeFrequency(rfileName);
	cout << "�ַ�" << setw(20) << "����Ƶ��" << setw(25) << "����������" << endl;
	Hf.HuffmanCoding();//�����������
	map<char, __int64>::iterator iter = Hf.frequencyMap.begin();
	for (int i = 0; i < Hf.frequencyMap.size(); i++)
	{
		cout << iter->first << setw(20) << iter->second << setw(25) << Hf.code[i] << endl;
		iter++;
	}
	Hf.GetBinaryCode();//��ȡ�����Ʊ���
	Hf.WriteFile(rfileName, wfileName);//���ù���������ѹ���ļ�
	cout << "ѹ�����" << endl;
	cout << "��ʼ����" << endl;
	Hf.Decode(wfileName);
	system("pause");
	return 0;
}