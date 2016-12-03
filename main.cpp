#include<iostream>
#include<math.h>
#include<stdlib.h>
#include<vector>
using namespace std;

class Vertice
{
	private:
		int numero;
		float peso;
	public:
		int getNumero();
		float getPeso();
		void setNumero(int);
		void setPeso(float);
};
int Vertice::getNumero()
{
	return numero;
}
float Vertice::getPeso()
{
	return peso;
}
void Vertice::setNumero(int num)
{
	this->numero = num;
}
void Vertice::setPeso(float p)
{
	this->peso = p;
}


class Grafo {
public:
	std::vector<vector<Vertice> > MatrixDeAdjacencia;
	// essa matriz e suas funções são feitas para auxiliar no desenvolvimento do algoritimo de PRim
	std::vector<vector<Vertice> > MatrixDeAdjacenciaDoPrim;
	Grafo(int NumeroDeVertices);
	void InserirPeso(int inicio, int fim, float peso);
	void InseirPesoPrim(int inicio, int fim, float peso);
	float GetPesoMatrixAdjacencia(int inicio, int fim);
	float GetPesoMatrixAdjacenciaPrim(int inicio, int fim);
	Vertice GetVerticeMatrixAdjacencia(int inicio, int fim);
	Vertice GetVerticeMatrixAdjacenciaDoPrim(int inicio, int fim);

};
Grafo::Grafo(int n) {
	for (int i = 0; i<n; i++) {
		std::vector<Vertice> vector;
		this->MatrixDeAdjacencia.push_back(vector);
		this->MatrixDeAdjacenciaDoPrim.push_back(vector);
		for (int j = 0; j<n; j++) {
			Vertice v;
			v.setNumero(j);
			v.setPeso(0);
			this->MatrixDeAdjacencia[i].push_back(v);
			this->MatrixDeAdjacenciaDoPrim[i].push_back(v);
		}
	}
}
void Grafo::InserirPeso(int origem, int destino, float peso) {
	this->MatrixDeAdjacencia[origem][destino].setPeso(peso);
	this->MatrixDeAdjacencia[destino][origem].setPeso(peso);

}
void Grafo::InseirPesoPrim(int inicio, int fim, float peso) {
	this->MatrixDeAdjacenciaDoPrim[inicio][fim].setPeso(peso);
	this->MatrixDeAdjacenciaDoPrim[fim][inicio].setPeso(peso);
}
float Grafo::GetPesoMatrixAdjacencia(int inicio, int fim) {
	float aux = this->MatrixDeAdjacencia[inicio][fim].getPeso();
	return aux;
}
float Grafo::GetPesoMatrixAdjacenciaPrim(int inicio, int fim) {
	float aux = this->MatrixDeAdjacenciaDoPrim[inicio][fim].getPeso();
	return aux;
}

Vertice Grafo::GetVerticeMatrixAdjacencia(int u, int v) {
	return this->MatrixDeAdjacencia[u][v];
}
Vertice Grafo::GetVerticeMatrixAdjacenciaDoPrim(int u, int v) {
	return this->MatrixDeAdjacenciaDoPrim[u][v];
}
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
	bool isEmpty();
	bool isQueued(Vertice);
};
bool heap_min_priority_queue::isQueued(Vertice v)
{
	for (int i = 1 ; i <= heap_size ; i++)
	{
		if (Queue[i].getNumero() == v.getNumero())
		{
			return true;
		}
	}
	return false;
}
bool heap_min_priority_queue::isEmpty()
{
	if (heap_size == 0)
	{
		return true;
	}
	return false;
}
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

	if (l <= heap_size && Queue[i].getPeso() > Queue[l].getPeso())
	{
		smallest = l;
	}
	else
	{
		smallest = i;
	}
	if (r <= heap_size && Queue[r].getPeso() < Queue[smallest].getPeso())
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

	Decrease_key(heap_size, vertice.getPeso());
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
	min.setPeso(-1);
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

	if (key > Queue[i].getPeso())
	{
		return false;
	}

	Queue[i].setPeso(key);

	while (i > 1 && Queue[Parent(i)].getPeso() > Queue[i].getPeso())
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
		if (value == Queue[i].getNumero())
		{
			if (key > Queue[i].getPeso())
			{
				return;
			}

			Queue[i].setPeso(key);

			while (i > 1 && Queue[Parent(i)].getPeso() > Queue[i].getPeso())
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

	v[1].setNumero(1);
	v[2].setNumero(2);
	v[3].setNumero(3);
	v[4].setNumero(4);
	v[5].setNumero(5);

	v[1].setPeso(10);
	v[2].setPeso(2);
	v[3].setPeso(1);
	v[4].setPeso(5);
	v[5].setPeso(4);

	heap_min_priority_queue fila;
	Vertice vertice;

	for (int i = 1; i < 6; i++)
	{
		fila.Insert(v[i]);
	}
	for (int i = 1; i < 6; i++)
	{
		
		vertice = fila.Extract_min();
		cout << vertice.getNumero() << ", " << vertice.getPeso() << endl;
		cout << "fila vazia? " << fila.isEmpty() << endl;
		cout << "vertice 4 tah na fila? " << fila.isQueued(v[4]) << endl;
	}


	Grafo graph(10);
	Vertice v1, v2;
	graph.InserirPeso(5, 6, 22.5);
	v1 = graph.GetVerticeMatrixAdjacencia(5, 6);
	v2 = graph.GetVerticeMatrixAdjacencia(6, 5);
	cout << "O peso de v1 eh: " << v1.getPeso() << "O numero de v1 eh :" << v1.getNumero() << "\n";
	cout << "O peso de v2 eh: " << v2.getPeso() << "O numero de v2 eh :" << v2.getNumero();

	//para segurar o console
	cin >> tt;
	// 3, 2, 5, 4, 1
	return 0;
}

