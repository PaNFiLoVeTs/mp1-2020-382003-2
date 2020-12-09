#include"stdio.h"
#include"stdbool.h"
#include"locale.h"
#include"stdlib.h"
#include"windows.h"
void menu()
{
	printf("\nMENU:\n");
	printf("1. Ввести размер массива\n");
	printf("2. Ввести элементы массива\n");
	printf("3. Отсортировать массив\n");
	printf("4. Распечатать массив\n");
	printf("0. Завершить работу программы\n");
}

void menu_Array()
{
	printf("\nMENU:\n");
	printf("1. Ввести массив\n");
	printf("2. Сгенерировать массив\n");
}

void menu_Sorts()
{
	printf("\nMENU:\n");
	printf("1. Быстрая сортировка\n");
	printf("2. Сортировка слиянием\n");
	printf("3. Сортировка Шелла(Р.Седжвик)\n");
	printf("4. Сортировка Шелла\n");
	printf("5. Сортировка вставками\n");
	printf("6. Сортировка расчёской\n");
	printf("7. Шейкерная Сортировка\n");
	printf("8. Сортировка пузырьком\n");
}

void Malloc(int** A, int Size)
{
	(*A) = (int*)malloc(sizeof(int) * Size);
}

void Size_f(int* Size)
{
	printf("Введите размер массива:");
	scanf_s("%d", Size);
}

void input(int** A, int Size)
{
	int i;
	int* B;
	B = (*A);
	printf("Введите элементы массива:");
	for (i = 0; i < Size; i++)
	{
		scanf_s("%d", &B[i]);
	}

}

void limits(int* Low, int* High)
{
	printf("Введите диапазон значений:");
	scanf_s("%d %d", Low, High);
}

void RandomArray(int** A, int Size)
{
	int i = 0, a = 0, b = 0;
	limits(&a, &b);
	for (i = 0; i < Size; i++)
	{
		(*A)[i] = rand() % (b - a) + a;
	}
}

void MemCopy(int** MainArray, int** CopyOfArray, int Size)
{
	int i = 0;
	for (i = 0; i < Size; i++)
	{
		(*CopyOfArray)[i] = (*MainArray)[i];
	}
}

void print(int** A, int Size)
{
	int i;
	int* B;
	B = (*A);
	for (i = 0; i < Size; i++)
	{
		printf("%d\t", B[i]);
	}
}

void Free(int** A)
{
	free(*A);
}

void QuickSort(int** A, int Left, int Right, int* ContrOfComp, int* ContrOfPer)
{
	int i = Left, j = Right - 1;
	int pivot = (*A)[(Left + j) / 2], tmp;
	do
	{
		while ((*A)[i] < pivot)
		{
			i++;
			(*ContrOfComp)++;
		}
		(*ContrOfComp)++;
		while ((*A)[j] > pivot)
		{
			(*ContrOfComp)++;
			j--;
		}
		(*ContrOfComp)++;
		if (i <= j)
		{
			tmp = (*A)[i];
			(*A)[i] = (*A)[j];
			(*A)[j] = tmp;
			(*ContrOfPer)++;
			i++;
			j--;
		}
		(*ContrOfComp)++;
	} while (i <= j);
	if (j > Left)
	{
		QuickSort(A, Left, j + 1, ContrOfComp, ContrOfPer);
	}
	if ((Right - 1) > i)
	{
		QuickSort(A, i, Right, ContrOfComp, ContrOfPer);
	}

}


void Merge(int** Target, int** Left, int LeftSize, int** Right, int RightSize, int* ContrOfComp)
{
	int LeftIndex = 0;
	int RightIndex = 0;
	int TargetIndex = 0;
	while ((LeftIndex < LeftSize) && (RightIndex < RightSize))
	{
		if ((*Left)[LeftIndex] < (*Right)[RightIndex])
		{
			(*ContrOfComp)++;
			(*Target)[TargetIndex] = (*Left)[LeftIndex];
			LeftIndex++;
		}
		else
		{
			(*ContrOfComp)++;
			(*Target)[TargetIndex] = (*Right)[RightIndex];
			RightIndex++;
		}
		TargetIndex++;
	}
	while (LeftIndex < LeftSize)
	{
		(*Target)[TargetIndex] = (*Left)[LeftIndex];
		LeftIndex++;
		TargetIndex++;
	}
	while (RightIndex < RightSize)
	{
		(*Target)[TargetIndex] = (*Right)[RightIndex];
		RightIndex++;
		TargetIndex++;
	}
}

void MergeSort(int** A, int Size, int* ContrOfComp)
{
	int i, LeftSize = 0, RightSize = 0, mid = Size / 2;
	int* Left = 0, * Right = 0;
	if (Size < 2)
	{
		return;
	}
	LeftSize = mid;
	RightSize = Size - mid;
	Malloc(&Left, LeftSize);
	Malloc(&Right, RightSize);
	for (i = 0; i < mid; i++)
	{
		Left[i] = (*A)[i];
	}
	for (i = mid; i < Size; i++)
	{
		Right[i - mid] = (*A)[i];
	}
	MergeSort(&Left, LeftSize, ContrOfComp);
	MergeSort(&Right, RightSize, ContrOfComp);
	Merge(A, &Left, LeftSize, &Right, RightSize, ContrOfComp);
	Free(&Left);
	Free(&Right);
}

int increments(int* inc, int Size)
{
	int i = -1, p1 = 1, p2 = 1, p3 = 1;
	do {
		if (++i % 2)
		{
			inc[i] = 8 * p1 - 6 * p2 + 1;
		}
		else
		{
			inc[i] = 9 * p1 - 9 * p3 + 1;
			p2 *= 2;
			p3 *= 2;
		}
		p1 *= 2;
	} while (3 * inc[i] < Size);
	if (Size > 3)
	{
		return i - 1;
	}
	else
	{
		return i;
	}

}

void ShellSortRS(int** A, int Size, int* ContrOfComp, int* ContrOfPer)
{
	int* inc = 0;
	int S, i, counter, tmp;
	Malloc(&inc, 40);
	S = increments(inc, Size);
	for (S; S >= 0; S--)
	{
		for (i = inc[S]; i < Size; i++)
		{
			counter = i;
			tmp = (*A)[i];
			while ((counter - inc[S] >= 0) && (tmp > (*A)[counter - inc[S]]))
			{
				(*ContrOfComp)++;
				(*A)[counter] = (*A)[counter - inc[S]];
				(*ContrOfPer)++;
				counter -= inc[S];
			}
			(*A)[counter] = tmp;
			(*ContrOfPer)++;
		}
	}
	Free(&inc);
}

void ShellSort(int** A, int Size, int* ContrOfComp, int* ContrOfPer)
{
	int Step = Size / 2, i, counter, tmp;
	for (Step = Size / 2; Step > 0; Step /= 2)
	{
		for (i = Step; i < Size; i++)
		{
			counter = i;
			tmp = (*A)[i];
			while ((counter - Step >= 0) && (tmp > (*A)[counter - Step]))
			{
				(*ContrOfComp)++;
				(*A)[counter] = (*A)[counter - Step];
				(*ContrOfPer)++;
				counter -= Step;
			}
			(*A)[counter] = tmp;
			(*ContrOfPer)++;
		}
	}
}

void InsertSort(int** A, int Size, int* ContrOfComp, int* ContrOfPer)
{
	int i, tmp, counter;
	tmp = 0;
	counter = 0;
	for (i = 1; i < Size; i++)
	{
		counter = i;
		tmp = (*A)[i];
		while ((counter > 0) && ((*A)[counter - 1] > tmp))
		{
			(*ContrOfComp)++;
			(*A)[counter] = (*A)[counter - 1];
			(*ContrOfPer)++;
			counter--;
		}
		(*A)[counter] = tmp;
		(*ContrOfPer)++;
	}
}

CombSort(int** A, int Size, int* ContrOfComp, int* ContrOfPer)
{
	int i, counter, tmp, Step;
	double Factor = 1.2473309;
	for (Step = Size - 1; Step > 0; Step = (int)(Step / Factor))
	{
		for (i = Step; i < Size; i++)
		{
			counter = i;
			while (((counter - Step) >= 0) && ((*A)[counter] < (*A)[counter - Step]))
			{
				(*ContrOfComp)++;
				tmp = (*A)[counter];
				(*A)[counter] = (*A)[counter - Step];
				(*A)[counter - Step] = tmp;
				(*ContrOfPer)++;
				counter -= Step;
			}
			(*ContrOfComp)++;
		}
	}
}

CocktailSort(int** A, int Size, int* ContrOfComp, int* ContrOfPer)
{
	int i, tmp, Left, Right;
	Right = Size - 1;
	Left = 0;
	while (Left < Right)
	{
		(*ContrOfComp)++;
		for (i = Left; i < Right; i++)
		{
			if ((*A)[i] > (*A)[i + 1])
			{
				(*ContrOfComp)++;
				tmp = (*A)[i];
				(*A)[i] = (*A)[i + 1];
				(*A)[i + 1] = tmp;
				(*ContrOfPer)++;
			}
			else
			{
				(*ContrOfComp)++;
			}

		}
		Right--;
		for (i = Right; i > Left; i--)
		{
			if ((*A)[i] < (*A)[i - 1])
			{
				(*ContrOfComp)++;
				tmp = (*A)[i];
				(*A)[i] = (*A)[i - 1];
				(*A)[i - 1] = tmp;
				(*ContrOfPer)++;
			}
			else
			{
				(*ContrOfComp)++;
			}
		}
		Left++;
	}
	(*ContrOfComp)++;
}

void BubbleSort(int** A, int Size, int* ContrOfComp, int* ContrOfPer)
{
	int i, j, tmp;
	for (i = 0; i < Size; i++)
	{
		for (j = 0; j < Size - i - 1; j++)
		{
			if ((*A)[j] > (*A)[j + 1])
			{
				(*ContrOfComp)++;
				tmp = (*A)[j];
				(*A)[j] = (*A)[j + 1];
				(*A)[j + 1] = tmp;
				(*ContrOfPer)++;
			}
			else
			{
				(*ContrOfComp)++;
			}
		}

	}
}

void main()
{
	LARGE_INTEGER freq, start, finish;
	QueryPerformanceFrequency(&freq);
	setlocale(LC_CTYPE, "Russian");
	int* A = 0, * B = 0;
	int Size = 0, Sw1 = 1, Sw2 = 0, Sw3 = 0;
	int ContrOfComp = 0, ContrOfPer = 0;
	double time;
	bool SizeInput = false;
	bool MassInput = false;
	bool ArrayCopy = false;
	while (Sw1)
	{
		menu();
		scanf_s("%d", &Sw1);
		switch (Sw1)
		{
		case 1:
		{
			if (MassInput)
			{
				Free(&A);
			}
			if (ArrayCopy)
			{
				Free(&B);
			}
			Size_f(&Size);
			SizeInput = true;
			MassInput = false;
			break;
		}
		case 2:
		{
			if (SizeInput)
			{
				menu_Array();
				scanf_s("%d", &Sw2);
				if (!MassInput)
				{
					Malloc(&A, Size);
				}
				if (ArrayCopy)
				{
					Free(&B);
				}
				switch (Sw2)
				{
				case 1:
				{
					input(&A, Size);
					ArrayCopy = false;
					break;
				}
				case 2:
				{
					RandomArray(&A, Size);
					ArrayCopy = false;
					break;
				}
				}
				MassInput = true;
			}
			else printf("Введите размер массива!");
			break;
		}
		case 3:
		{
			if (MassInput)
			{
				menu_Sorts();
				if (!ArrayCopy)
				{
					Malloc(&B, Size);
					ArrayCopy = true;
				}
				MemCopy(&A, &B, Size);

				scanf_s("%d", &Sw3);
				switch (Sw3)
				{
				case 1:
				{
					ContrOfComp = 0;
					ContrOfPer = 0;
					QueryPerformanceCounter(&start);
					QuickSort(&B, 0, Size, &ContrOfComp, &ContrOfPer);
					QueryPerformanceCounter(&finish);
					time = (double)(finish.QuadPart - start.QuadPart) / (double)freq.QuadPart;
					printf("time=%.10f Сравнения=%d Перестановки=%d", time, ContrOfComp, ContrOfPer);
					break;
				}
				case 2:
				{
					ContrOfComp = 0;
					ContrOfPer = 0;
					QueryPerformanceCounter(&start);
					MergeSort(&B, Size, &ContrOfComp);
					QueryPerformanceCounter(&finish);
					time = (double)(finish.QuadPart - start.QuadPart) / (double)freq.QuadPart;
					printf("time=%.10f Сравнения=%d Перестановки=%d", time, ContrOfComp, ContrOfPer);
					break;
				}
				case 3:
				{
					ContrOfComp = 0;
					ContrOfPer = 0;
					QueryPerformanceCounter(&start);
					ShellSortRS(&B, Size, &ContrOfComp, &ContrOfPer);
					QueryPerformanceCounter(&finish);
					time = (double)(finish.QuadPart - start.QuadPart) / (double)freq.QuadPart;
					printf("time=%.10f Сравнения=%d Перестановки=%d", time, ContrOfComp, ContrOfPer);
					break;
				}
				case 4:
				{
					ContrOfComp = 0;
					ContrOfPer = 0;
					QueryPerformanceCounter(&start);
					ShellSort(&B, Size, &ContrOfComp, &ContrOfPer);
					QueryPerformanceCounter(&finish);
					time = (double)(finish.QuadPart - start.QuadPart) / (double)freq.QuadPart;
					printf("time=%.10f Сравнения=%d Перестановки=%d", time, ContrOfComp, ContrOfPer);
					break;
				}
				case 5:
				{
					ContrOfComp = 0;
					ContrOfPer = 0;
					QueryPerformanceCounter(&start);
					InsertSort(&B, Size, &ContrOfComp, &ContrOfPer);
					QueryPerformanceCounter(&finish);
					time = (double)(finish.QuadPart - start.QuadPart) / (double)freq.QuadPart;
					printf("time=%.10f Сравнения=%d Перестановки=%d", time, ContrOfComp, ContrOfPer);
					break;
				}
				case 6:
				{
					ContrOfComp = 0;
					ContrOfPer = 0;
					QueryPerformanceCounter(&start);
					CombSort(&B, Size, &ContrOfComp, &ContrOfPer);
					QueryPerformanceCounter(&finish);
					time = (double)(finish.QuadPart - start.QuadPart) / (double)freq.QuadPart;
					printf("time=%.10f Сравнения=%d Перестановки=%d", time, ContrOfComp, ContrOfPer);
					break;
				}
				case 7:
				{
					ContrOfComp = 0;
					ContrOfPer = 0;
					QueryPerformanceCounter(&start);
					CocktailSort(&B, Size, &ContrOfComp, &ContrOfPer);
					QueryPerformanceCounter(&finish);
					time = (double)(finish.QuadPart - start.QuadPart) / (double)freq.QuadPart;
					printf("time=%.10f Сравнения=%d Перестановки=%d", time, ContrOfComp, ContrOfPer);
					break;
				}
				case 8:
				{
					ContrOfComp = 0;
					ContrOfPer = 0;
					QueryPerformanceCounter(&start);
					BubbleSort(&B, Size, &ContrOfComp, &ContrOfPer);
					QueryPerformanceCounter(&finish);
					time = (double)(finish.QuadPart - start.QuadPart) / (double)freq.QuadPart;
					printf("time=%.10f Сравнения=%d Перестановки=%d", time, ContrOfComp, ContrOfPer);
					break;
				}
				}
			}
			else printf("Error");
			break;
		}
		case 4:
		{
			if (MassInput)
			{
				if (!ArrayCopy)
				{
					Malloc(&B, Size);
					MemCopy(&A, &B, Size);
					ArrayCopy = true;
				}
				print(&B, Size);
			}
			else printf("Error");
			break;
		}
		}
	}
	if (MassInput)
	{
		Free(&A);
	}
	if (ArrayCopy)
	{
		Free(&B);
	}
}