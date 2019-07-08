#pragma once
#include <iostream>
#include <vector>

class BaseSort
{
public:
	BaseSort() {};
	~BaseSort() {};
	virtual void Sort(std::vector<int>& list) {};

	bool isSorted(std::vector<int>& list) {
		bool Sorted = true;
		for (unsigned int i = 1; i < list.size(); ++i)
		{
			if (list[i] < list[i - 1]) //Si el elemento en el que voy, es menor que el elemento anterior, no está organizada y debo correr el quicksort.
			{
				Sorted = false; //No está sorted.
				return Sorted;
			}
		}
	};
};

class BubbleSort : public BaseSort
{
public:
	BubbleSort() {};
	~BubbleSort() {};
	virtual void Sort(std::vector<int>& v) {
		if (!isSorted(v)) {
			RunBubbleSort(v);
		}
	}

private:
	void RunBubbleSort(std::vector<int> v) {
		unsigned int i, j;
		for (i = 0; i < v.size() - 1; ++i) {	// Cada valor de la lista
			for (j = 0; j < v.size() - i - 1; ++j) {	// Voy a compararlo con todo los demas
				if (v[j] > v[j + 1]) {	// Si el valor en el que estoy es mayor al siguiente
					int temp = v[j];	// Intercambio su posición utilizando un buffer(?) temporal para no perder los valores
					v[j] = v[j + 1];
					v[j + 1] = temp;
				}
			}
		}
	}
};

class InsertSort : public BaseSort {
public:
	InsertSort() {};
	~InsertSort() {};
	virtual void Sort(std::vector<int>& v) {
		if (!isSorted(v) && v.size() > 1) {
			RunInsertSort(v);
		}
	}
private:
	void RunInsertSort(std::vector<int> v) {
		unsigned int i;
		int j, val;
		for (i = 1; i < v.size(); ++i) {
			val = v[i];
			for (j = i - 1; j >= 0 && v[j] > val; --j) {
				v[j + 1] = v[j];
			}
			v[j + 1] = val;
		}
	}
};

//El hijo quicksort, su padre es baseSort.
class QuickSort : public BaseSort //Lleva public porque quieres que "herede" todo de manera publica. O sea que lo pueda ver sin problemas el hijo.
{
public:
	QuickSort() {};
	~QuickSort() {};
	//La función del hijo del sort. Esta y la de arriba, llevan virtual, porque virtual lo que hace, es habilitar el polimorfismo.
	//Cuando tienes punteros, que son variables que guardan direcciones en memoria a otras variables, Puedes usar un puntero del padre, para 
	//manejar a los hijos como si fueran el padre. Eso es la parte polimorfica, poli es muchas o varias y morfismo, pues viene de forma, que viene del griego morfo que significa forma. Obiamente, soi 100tifiko.
	//entonces tu variable quicksort hijo puede tomar varias formas, puede "ser" un BaseSort o puede "ser" un Quicksort, que es su forma verdadera y más completa en realidad. Pero solamente funciona con punteros.
	//Entonces si yo hago un puntero a baseSort así: BaseSort* puntero = new QuickSort(); Ahi le estoy diciendo que cree un puntero de tipo BaseSort, o sea que apunta a la dirección de memoria de un objeto de tipo "BaseSort"
	//pero le igualo la dirección en memoria de un objeto de tipo "QuickSort", o sea su hijo, y no hay problema, puedes manejar al objeto "Hijo" a traves de su forma o interfaz Padre.
	virtual void Sort(std::vector<int>& list) //Recibo la list con un "&", eso es para decirle que me tome el parametro por refencia, o sea, que cualquier cambio que le haga a list, se lo haré al objeto original, porque estoy trabajando con su dirección en memoria, no con una copia del objeto original.
	{
		if (!isSorted(list) && list.size() > 1) {
			list = RunQuickSort(list);
		}

	}

	//Cosas que puedo explicar de aqui arriba: MUY IMPORTANTES
	//un puntero se llama con *. Si ven un asterisco al lado de variables que no son aritmeticas o simples numeros, tiene que ver con punteros. 
		//Por ejemplo, un puntero a un objeto de tipo/clase quicksort se crea así: "QuickSort* ptr;" Y ya, ptr es una variable lista para tomar valores de direcciones de memoria.
	//una referencia se llama con &. Lo que hace eso, es sacar la dirección de cualquier variable, aunque no sea dinamicamente alojada. 
		//Por ejemplo: "int perro = 4;" La variable perro es igual a 4, pero no sé donde está en memoria, para saberlo, podria hacer esto "int* punteroAPerro = &perro;"
	//Ahora tengo la dirección de memoria de la variable perro, en mi punteroAPerro.
	//Busquen como usar punteros y la diferencia con refrencias en internet.

	//new Algo(); Cuando llamas "new", le estas diciendo al compilador que quieres crear un nuevo objeto dinamicamente en memoria.
	//Hay 2 tipos de memoria al programar. El Stack, que es donde se van guardando todas las variables normales, que vas definiendo adentro de funciones y así. Es la memoria normal de tu programa, ya asignada y controlada.
	//Cuando tu defines una variable adentro de una función como así "int var;" esa variable se guarda dentro del stack de esa función,
	//un stack es memoria que va asignando el programa mientras la vas necesitando dentro de un scope o contexto, cuando sale del scope de la función, se destruye esa memoria y esa variable..
	//El heap, es memoria pura, sin contexto. Tu puedes tomar de esa memoria para hacer y guardar variables ahí, eso se hace utilizando new y delete.
	//Ya que esta memoria no es controlada por el programa, sino "libre" para que tu agarres y sueltes.
	//tu eres el que tiene que controlarla, usando new y delete. new es como decirle "creame un nuevo objeto de este tipo en el heap y regresame la dirección donde lo creaste".
	//delete es decirle "borrame este objeto de este tipo en esta dirección".
	//Por eso se utilizan punteros, porque para manejar memoria dinamica, tienes que conocer donde está en memoria, o sea su dirección, o sea un puntero.
	//https://codingornot.com/diferencias-entre-heap-y-stack Pagina donde hablan del heap y el stack.

private:

	//Esta es una función privada, que recibe un vector con elementos enteros en un parametro llamado "list"
	//Regresa lo mismo, un vector con elementos enteros.
	//Es privada porque no quiero que la llamen desde fuera, lo que quiero que llamen desde fuera es Sort().
	//Pero esta es la función que tiene la logica y la recursividad.
	std::vector<int> RunQuickSort(std::vector<int> list)
	{
		//Saca el tamaño de la lista.
		int Size = list.size();

		//Si el tamaño es 1 o menor, no hay nada que organizar.
		if (Size < 2)
		{
			//Regresa la misma lista
			return { list };
		}

		//Maiki propuso esto en clase, de que checar si ya estaba organizado o no, pero pues no me dijo de qué manera.
		//Entonces pues la más simple sería caminar la lista hasta encontrar 1 que no esté acomodado.

		//Asumimos que está organizado ya.
		bool Sorted = true;

		//Me dijeron que no sabian como funcionaba el for en C++.

		//for (Expresión-de-inicio; Condición; incremento)
		//{
		//	Instrucciones del ciclo.
		//}

		//La expresión de inicio se corre una vez, al principio, cuando llega a esa linea del for.

		//La condición se corre cada vez que va a entrar a las instrucciones adentro del for, para ver si puede entrar o no.

		//El incremento se corre cada vez que termina las instrucciones adentro del for, es donde manejas el contador y cambias variables para que
		//se deje de cumplir la condición y "termine" el for.

		//Lo saqué de aquí, el primer resultado cuando buscas C++ for y está en español, no tienen excusa. https://ehack.info/ciclo-for-en-c/

		//Ejemplo de for: for (int i = 0; i < vector.size(); ++i) {	Instrucciones }
		//Ese for declara e inicializa una variable i en 0, para que empiece a contar desde el 0, como en toda la programación, se empieza desde el 0.
		//Luego pone una condición, de si i es menor que el tamaño del vector, Si tenemos 5 elementos en el vector, el i va a tomar los valores 0, 1, 2, 3, 4
		//el 5 ya no porque ya no es menor que el tamaño del vector, ya es igual.
		//Por ultimo, dice que el incremento es ++i, el "++" es un operador de incremento, es igual que decir "i = i+1;" Busquen la diferencia entre ponerlo así ++i y ponerlo así i++.
			// ++i -> incrementa el valor de i antes de devolverlo | i++ -> devuelve el valor de i y despues lo incrementa.
		//entonces, va subiendo i de uno por uno, hasta que se vuelve igual al tamaño del vector y ya no entra, o sea que pasamos por todos los elementos del vector con ese for.
		//Fin de explicación del for.

		//Pasar por todos mis elementos, desde el segundo, para poder comparar con el anterior. 
		//Si empezaramos desde el 0, cuando quisieras comparar con el anterior explotaria.
		for (unsigned int i = 1; i < list.size(); ++i)
		{
			if (list[i] < list[i - 1]) //Si el elemento en el que voy, es menor que el elemento anterior, no está organizada y debo correr el quicksort.
			{
				Sorted = false; //No está sorted.
				break;
			}
		}

		//Si Sorted es verdad, ya estaba organizada desde el principio, entonces podemos regresar la misma lista, porque ya está organizada.
		if (Sorted == true)
		{
			return list;
		}

				//Esta no es la mejor forma de escoger el valor del pivote, pero sirve ahorita.
				//Tenemos que escoger un valor de pivote, entonces pues nada más hacemos un random entre todos los elementos de la lista.
		int pivotValue = list[rand() % Size];
		//rand() te puede regresar numeros grandisimos, negativos y positivos, pero si usas el modulo (%), que te da el residuo de la división.
		//Puedes limitarlo a que sea un numero del 0 al Size, o lo que pongas despues del "%"

		std::vector<int> leftList; //La lista de elementos menores que el pivote  y tambien le metemos los que sean iguales que el pivote porque si no esos elementos, desaparecerian.
		std::vector<int> rightList; //La lista de elementos mayores que el pivote.

		for (unsigned int i = 0; i < list.size(); ++i) //El buen for que pasa por todos los elementos, explicado arriba.
		{
			if (list[i] <= pivotValue) //Si el valor en el indice que voy, es menor que el valor del pivote.
			{
				leftList.push_back(list[i]); //Empujalo en la lista izquierda.
			}
			else if (list[i] > pivotValue) //Si el valor en el indice que voy, es mayor que el valor del pivote.
			{
				rightList.push_back(list[i]); //Empujalo en la lista derecha.
			}
		}

		std::vector<int> leftListSorted; //Otros nuevos vectores donde guardaremos la lista izquierda y la lista derecha, pero organizadas.
		std::vector<int> rightListSorted;

		//Esto es recursión. Es cuando una función se llama a sí misma, con otras condición o parametros, para que haga el mismo trabajo pero
		//sobre un grupo de datos más chico cada vez. Ustedes lo vieron, tienes la lista original, la divides entre dos, y haces lo mismo
		//y eso lo divides entre dos y vuelves a hacer lo mismo y así y así, hasta que ya solamente son listas de 1 elemento. Eso es recursividad.
		//Así se aplica.
		leftListSorted = RunQuickSort(leftList); //Ahora, corro esta misma función en donde estoy, pero con la lista de elementos menores que el pivote.
		rightListSorted = RunQuickSort(rightList); //Al mismo tiempo, corro esta misma función, pero con la lista de elementos mayores que el pivote.

		//Al final, las combino, agregandole a la de la izquierda, todos los de la derecha.
		for (unsigned int i = 0; i < rightListSorted.size(); ++i)
		{
			leftListSorted.push_back(rightListSorted[i]); //Empujar a la lista de la izquierda, cada uno de la lista derecha.
		}

		return leftListSorted; //regresar la lista de la izquierda, que ya tiene combinado, la lista derecha.
	}

private:

};