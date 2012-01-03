using namespace std;
#include<iostream>

class Complex{
	float real;
	float imag;
public:
	Complex();
	Complex(float a,float b);
	void print()
	{
		cout << real << '+' << imag << 'i' << endl;
	}
	Complex operator + (Complex op2);
	Complex operator - (Complex op2);
	Complex operator * (Complex op2);
	Complex operator / (Complex op2);
	Complex operator = (Complex op2);
};

Complex :: Complex()
{
	real = 0;
	imag = 0;
}

Complex :: Complex(float a,float b)
{
	real = a;
	imag = b;
}

Complex Complex :: operator +(Complex op2)
{
	Complex temp;
	temp.real = real + op2.real;
	temp.imag = imag + op2.imag;
	return temp;
}

Complex Complex :: operator - (Complex op2)
{
	Complex temp;
	temp.real = real - op2.real;
	temp.imag = imag - op2.imag;
	return temp;
}

Complex Complex :: operator * (Complex op2)
{
	Complex temp;
	temp.real = real*op2.real - imag*op2.imag;
	temp.imag = real*op2.imag + imag*op2.real;
	return temp;
}

Complex Complex :: operator / (Complex op2)
{
	Complex conj(op2.real,-op2.imag);
	Complex temp(real,imag);
	temp = temp * conj;
	temp = temp * Complex(1/(op2.real*op2.real + op2.imag*op2.imag),0);
	return temp;
}

Complex Complex :: operator = (Complex op2)
{
	Complex temp;
	real = op2.real;
	imag = op2.imag;
}

int main()
{
	Complex a[5] = {Complex(1,1),Complex(2,2),Complex(3,3),Complex(4,4),Complex(5,5)};
	Complex temp;
	int i,j;
	cout << "1+1j , 2+2j\n";
	cout <<"*********************"<<endl;
	temp = a[0] + a[1];
	temp.print();
	temp = a[0] - a[1];
	temp.print();
	temp = a[0] * a[1];
	temp.print();
	temp = a[0] / a[1];
	temp.print();
	cout << "2+2j , 3+3j\n";
	cout <<"*********************"<<endl;
	temp = a[1] + a[2];
	temp.print();
	temp = a[1] - a[2];
	temp.print();
	temp = a[1] * a[2];
	temp.print();
	temp = a[1] / a[2];
	temp.print();
}
