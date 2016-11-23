#include<iostream>
#include<math.h>
#include<stdlib.h>

using namespace std;

class Vertice
{
	private:

	public:
		int numero;
		int peso;
};
class heap_min_priority_queue
{
	private:
		int heap_size;
		int infinite;
		Vertice Queue[51];
		int Parent(int i);
		int Left(int i);
		int Right(int i);

	public:
		heap_min_priority_queue();
		void build_min_heap();
		void Min_heapify(int i);
		void Insert(Vertice);
		Vertice Minimum();
		Vertice Extract_min();
		bool Decrease_key(int i, int key);
		void Increase_Priority(int value, int key);
};
heap_min_priority_queue::heap_min_priority_queue()
{
	heap_size = 0;
	infinite = 9999;
};

void heap_min_priority_queue::build_min_heap()
{

	for (int i = (int)trunc(heap_size / 2); i >= 1; i--)
	{
		Min_heapify(i);
	}
};
void heap_min_priority_queue::Min_heapify(int i)
{
	int l = Left(i);
	int r = Right(i);
	int smallest;
	Vertice aux;

	if (l <= heap_size && Queue[i].peso > Queue[l].peso)
	{
		smallest = l;
	}
	else
	{
		smallest = i;
	}
	if (r <= heap_size && Queue[r].peso < Queue[smallest].peso)
	{
		smallest = r;
	}
	if (smallest != i)
	{
		//troca os vertices
		aux = Queue[i];
		Queue[i] = Queue[smallest];
		Queue[smallest] = aux;

		Min_heapify(smallest);
	}
};
void heap_min_priority_queue::Insert(Vertice vertice)
{
	//aumenta a quantidade de itens na fila
	heap_size++;

	//indice 0 é a key
	Queue[heap_size] = vertice;

	Decrease_key(heap_size, vertice.peso);
	Min_heapify(heap_size);
	//build_min_heap();
};
Vertice heap_min_priority_queue::Minimum()
{
	return Queue[1];
}
Vertice heap_min_priority_queue::Extract_min()
{
	Vertice min;
	min.peso = -1;
	if (heap_size < 1)
	{
		return min;
	}

	//int min = A[1];
	min = Queue[1];

	Queue[1] = Queue[heap_size];

	heap_size -= 1;

	Min_heapify(1);

	return min;
};
bool heap_min_priority_queue::Decrease_key(int i, int key)
{
	Vertice aux;

	if (key > Queue[i].peso)
	{
		return false;
	}

	Queue[i].peso = key;

	while (i > 1 && Queue[Parent(i)].peso > Queue[i].peso)
	{
		//troca de chaves
		aux = Queue[i];
		Queue[i] = Queue[Parent(i)];
		Queue[Parent(i)] = aux;

		i = Parent(i);
	}
	return true;
};
void heap_min_priority_queue::Increase_Priority(int value, int key)
{
	Vertice aux;

	for (int i = 1; i <= heap_size; i++)
	{
		if (value == Queue[i].numero)
		{
			if (key > Queue[i].peso)
			{
				return;
			}

			Queue[i].peso = key;

			while (i > 1 && Queue[Parent(i)].peso > Queue[i].peso)
			{
				//troca de chaves
				aux = Queue[i];
				Queue[i] = Queue[Parent(i)];
				Queue[Parent(i)] = aux;

				i = Parent(i);
			}
			return;
		}
	}



};
int heap_min_priority_queue::Parent(int i)
{
	return (int)trunc(i / 2);
};
int heap_min_priority_queue::Left(int i)
{
	return 2 * i;
};
int heap_min_priority_queue::Right(int i)
{
	return 2 * i + 1;
};


int main()
{
	int tt;
	Vertice v[6];

	v[1].numero = 1;
	v[2].numero = 2;
	v[3].numero = 3;
	v[4].numero = 4;
	v[5].numero = 5;

	v[1].peso = 10;
	v[2].peso = 2;
	v[3].peso = 1;
	v[4].peso = 5;
	v[5].peso = 4;

	heap_min_priority_queue fila;
	Vertice vertice;

	for (int i = 1; i < 6; i++)
	{
		fila.Insert(v[i]);
	}
	for (int i = 1; i < 6; i++)
	{
		vertice = fila.Extract_min();
		cout << vertice.numero << ", " << vertice.peso << endl;
	}

	//para segurar o console
	cin >> tt;
	// 3, 2, 5, 4, 1
	return 0;
}

