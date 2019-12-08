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
	cout << "字符" << setw(20) << "出现频率" << setw(25) << "哈弗曼编码" << endl;
	Hf.HuffmanCoding();//构造哈夫曼树
	map<char, __int64>::iterator iter = Hf.frequencyMap.begin();
	for (int i = 0; i < Hf.frequencyMap.size(); i++)
	{
		cout << iter->first << setw(20) << iter->second << setw(25) << Hf.code[i] << endl;
		iter++;
	}
	Hf.GetBinaryCode();//获取二进制编码
	Hf.WriteFile(rfileName, wfileName);//利用哈夫曼编码压缩文件
	cout << "压缩完成" << endl;
	cout << "开始解码" << endl;
	Hf.Decode(wfileName);
	system("pause");
	return 0;
}