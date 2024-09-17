#include <iostream>
#include <time.h>

void Fact(int N) { // вычисление N!

	int f = 1;
	for (int i = 1; i <= N; i++) {
		f *= i;
	}
}


int main() {
	clock_t start = clock(); // время до выполнения кода

	int N = 10;
	int i = 1;
	
	while (i < 10000000) { // 10 млн. раз вычисляем 10! 
		Fact(N);
		i++;
	}

	clock_t end = clock(); // время после выполнения кода
	double seconds = (double)(end - start) / CLOCKS_PER_SEC; // время выполнения кода в секундах

	std::cout << seconds << std::endl;
}

