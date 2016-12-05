#include<iostream>
#include<math.h>
#include<stdlib.h>
#include<vector>
using namespace std;

class Vertice
{
private:
	int numero, antecessor;
	float peso, chave;
public:
	int getNumero();
	float getPeso();
	int getAntecessor();
	float getChave();
	void setNumero(int);
	void setPeso(float);
	void setAntecessor(int);
	void setChave(float);
};
int Vertice::getNumero()
{
	return numero;
}
float Vertice::getPeso()
{
	return peso;
}
int Vertice::getAntecessor()
{
	return antecessor;
}
float Vertice::getChave()
{
	return chave;
}
void Vertice::setNumero(int num)
{
	this->numero = num;
}
void Vertice::setChave(float c)
{
	this->chave = c;
}

void Vertice::setAntecessor(int ant)
{
	this->antecessor = ant;
}
void Vertice::setPeso(float p)
{
	this->peso = p;
}

class heap_min_priority_queue
{
private:
	int heap_size;
	int infinite;
	Vertice Queue[100];
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
	bool Decrease_key(int i, float key);
	void Increase_Priority(int value, float key);
	int isEmpty();
	int isQueued(Vertice);
};

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
	float Prim(Grafo grafo, int raiz, int ordem);

};

Grafo::Grafo(int n) {
	for (int i = 0; i<n; i++) {
		std::vector<Vertice> vector;
		this->MatrixDeAdjacencia.push_back(vector);
		this->MatrixDeAdjacenciaDoPrim.push_back(vector);
		for (int j = 0; j<n; j++) {
			Vertice v;
			v.setNumero(j);
			v.setPeso(99999);
			v.setAntecessor(-1);
			v.setChave(9999);
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

float Grafo::Prim(Grafo grafo, int raiz, int ordem) {

	heap_min_priority_queue Q;
	Vertice v, u;
	int i;
	float peso = 0;
	vector<Vertice>parada(ordem);
	u.setChave(0);
	u.setNumero(raiz-1);
	Q.Insert(u);
	parada[raiz-1].setAntecessor(0);
	parada[raiz-1].setPeso(0);
	for (i = 0; i<ordem; i++) {
		u.setChave(99999);
		if(i!=raiz-1){
			u.setNumero(i);
			parada[i].setAntecessor(-1);
			parada[i].setChave(999999);
			Q.Insert(u);
		}
	}
	while (Q.isEmpty() != true) {

		u = Q.Extract_min();

		for (i = 0; i<ordem; i++) {
			v = grafo.GetVerticeMatrixAdjacencia(u.getNumero(), i);
			if ((Q.isQueued(this->MatrixDeAdjacencia[u.getNumero()][i]) == true)&& (this->MatrixDeAdjacencia[u.getNumero()][i].getPeso()<v.getChave())&&(this->MatrixDeAdjacencia[u.getNumero()][i].getPeso()!=-1)) {
				v.setChave(this->MatrixDeAdjacencia[u.getNumero()][i].getPeso());
				if(v.getChave()<parada[v.getNumero()].getChave()){
					parada[v.getNumero()].setNumero(v.getNumero());
					parada[v.getNumero()].setAntecessor(u.getNumero());
					parada[v.getNumero()].setChave(this->MatrixDeAdjacencia[u.getNumero()][i].getPeso());
				}
				Q.Increase_Priority(v.getNumero(),v.getChave());
			}
		}
	}

	for(int i=0; i<ordem; i++){
		peso+=parada[i].getChave();
	}
	return peso;

}

int heap_min_priority_queue::isQueued(Vertice v)
{
	for (int i = 1; i <= heap_size; i++)
	{
		if (Queue[i].getNumero() == v.getNumero())
		{
			return 1;
		}
	}
	return 0;
}
int heap_min_priority_queue::isEmpty()
{
	if (heap_size == 0)
	{
		return 1;
	}
	return 0;
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

	if (l <= heap_size && Queue[i].getChave() > Queue[l].getChave())
	{
		smallest = l;
	}
	else
	{
		smallest = i;
	}
	if (r <= heap_size && Queue[r].getChave() < Queue[smallest].getChave())
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

	Decrease_key(heap_size, vertice.getChave());
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
	min.setChave(-1);
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
bool heap_min_priority_queue::Decrease_key(int i, float key)
{
	Vertice aux;

	if (key > Queue[i].getChave())
	{
		return false;
	}
	Queue[i].setChave(key);

	while (i > 1 && Queue[Parent(i)].getChave() > Queue[i].getChave())
	{
		//troca de chaves
		aux = Queue[i];
		Queue[i] = Queue[Parent(i)];
		Queue[Parent(i)] = aux;

		i = Parent(i);
	}
	return true;
};
void heap_min_priority_queue::Increase_Priority(int value, float key)
{
	Vertice aux;

	for (int i = 1; i <= heap_size; i++)
	{
		if (value == Queue[i].getNumero())
		{
			if (key > Queue[i].getChave())
			{
				return;
			}

			Queue[i].setChave(key);

			while (i > 1 && Queue[Parent(i)].getChave() > Queue[i].getChave())
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

	int ordem, tamanho, raiz, v1, v2;
	float peso;
	cout << "Ordem e tamanho" << endl;
	cin >> ordem >> tamanho;
	Grafo graph(ordem);
	for (int i = 0; i<tamanho; i++) {
		cout << "v1, v2, peso: " << i << endl;
		cin >> v1 >> v2 >> peso;
		graph.InserirPeso(v1 - 1, v2 - 1, peso);
	}
	cout << "raiz" << endl;
	cin >> raiz;
	cout<<"peso: "<<graph.Prim(graph, raiz, ordem)<<endl;

	/*heap_min_priority_queue fila;
	Vertice v1, v2, v3, u;
	v1.setNumero(1);
	v1.setChave(1.5);
	v2.setNumero(2);
	v2.setChave(1.9);
	v3.setNumero(3);
	v3.setChave(0.9);
	fila.Insert(v1);
	fila.Insert(v2);
	fila.Insert(v3);
	u = fila.Extract_min();
	cout << "extraiu " << u.getNumero() << endl;
	u = fila.Extract_min();
	cout << "extraiu " << u.getNumero() << endl;
	u = fila.Extract_min();
	cout << "extraiu " << u.getNumero() << endl;
	return 0;*/
}

