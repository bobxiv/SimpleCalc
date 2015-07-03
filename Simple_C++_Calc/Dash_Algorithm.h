#pragma once

#ifndef DASH_ALGORITHMS

#define DASH_ALGORITHMS


#include "Dash_Tree.h"
#include "Dash_BTree.h"
#include "Dash_List.h"
#include "Dash_MapL.h"



namespace AED_Parciales{//usando mis estructuras

	bool odd( int val){
	if( val % 2 ){
		return true;
		}
	return false;

	}

	void Tree_count( Dash_Structures::DTree<int> &A , Dash_Structures::_Tree_Iterator<int> p, int& cant){

	//cant debe entrar la primera vez como 0

	if( p == A.end() ){
		return;	
		}

	cant++;

	Dash_Structures::DTree<int>::iterator q = p.lchild();

	while( q != A.end() ){
		Tree_count( A,q,cant);
		q++;
		}

	

	}


	//borra todos los nodos de un arbol binario que sean impares
	void Bprune_odd( Dash_Structures::DBTree<int> & _T , Dash_Structures::DBTree<int>::iterator _p ){

		 if( _p == _T.end() )//Si es lamda no hago nada
			 return;

		if( (*_p % 2) == 0  ){//Si es par, borro los hijos impares
			Bprune_odd( _T , _p.left_child() );

			Bprune_odd( _T , _p.right_child() );

			return;

			}
			
		_T.erase( _p );//Si es impar lo borro, borrando todos sus hijos... nota: erase -> O( n )
		return;

	}

		//WRAPPER
	//borra todos los nodos de un arbol binario que sean impares
	void Bprune_odd( Dash_Structures::DBTree<int> & _T ){

		Bprune_odd( _T , _T.begin() );
		return;
	}

	//borra un nodo si cumple con el predicado, en un arbol BINARIO... funcion pred
	//Buen ejemplo de programacion funcional
	void Bremove_if( Dash_Structures::DBTree<int> & _T , Dash_Structures::DBTree<int>::iterator _p , bool (*pred)(int) ){

		if( _p == _T.end() )//Si es lamda no hago nada
			return;

		if( ! pred( *_p ) ){//Si no cumple con pred, pregunto por susdos hijos
			Bremove_if( _T, _p.left_child() , pred );

			Bremove_if( _T , _p.right_child() , pred );

			return;

			}

		_T.erase( _p );//Si cumple con pred luegose borra
		return;

		}

		//WRAPPER
	//borra un nodo si cumple con el predicado, en un arbol BINARIO... funcion pred
	//Buen ejemplo de programacion funcional
	void Bremove_if( Dash_Structures::DBTree<int> & _T , bool (*pred)(int) ){

		Bremove_if( _T , _T.begin() , pred );

		}

	void Bcount_if( Dash_Structures::DBTree<int> & T , Dash_Structures::DBTree<int>::iterator p , bool (*pred)(int), int& count ){

		if( p == T.end() )//si pregunta lamda, no hago nada
			return;

		if( pred( *p ) )
			count++;//si cumple lo cuento

		//ahora pregunto por los hijos
		Dash_Structures::DBTree<int>::iterator l = p.left_child();
		Dash_Structures::DBTree<int>::iterator r = p.right_child();

		Bcount_if( T , l , pred , count );
		Bcount_if( T , r , pred , count );

		return;


		}

	void Bcount_if( Dash_Structures::DBTree<int> & T , bool (*pred)(int) , int& count ){

		Bcount_if( T , T.begin() , pred , count );

		}

	//recorre el arbol en preorden y si cumple con pred lo agrega a la lista, para arboles ordenados orientados
	void list_if( Dash_Structures::DTree<int> & T , Dash_Structures::DTree<int>::iterator p , bool(*pred)(int) , 
		Dash_Structures::DList<int> & L){

			if( p == T.end() )//si es que es vacio, no hago nada
				return;


			if( pred( *p ) ){//me fijo en el valor del nodo padre y lo guardo si cumple con la condicion
				L.push_back( *p );// como es preorden primero proceso despues recorro hijos, de izquierda a derecha
				}

			Dash_Structures::DTree<int>::iterator c = p.lchild();

			while( c != T.end() ){//recorre y ejecuto en todos sus hijos, porque es en preorden
				list_if( T , c++ , pred , L );
				}

			return;

		}

		//WRAPPER
	//recorre el arbol en preorden y si cumple con pred lo agrega a la lista, para arboles ordenados orientados
	void list_if( Dash_Structures::DTree<int> & T , bool(*pred)(int) , Dash_Structures::DList<int> & L){
		
		list_if( T , T.begin() , pred , L );
		return;

		}
		

	//es para un arbol binario, lo que hace es recorrer las hojasde arbol, y si alguna es menor que elparametro min_leaf
	//luego borro la hoja y le sumo su valor a el padre.
	int Bremove_leaf( Dash_Structures::DBTree<int> & T , Dash_Structures::DBTree<int>::iterator & p,
		int min_leaf){

			if( p == T.end() ) //Si entra nodo vacio retorno 0, entonces no me afecta el tamaño del padre
				return 0;

			//pregunto por los hijos, si es que soy hoja, no me afecta preguntar, y si lo soy
			//si pregunto antes si soy hoja despues de fijarme por los hijos puedo ser una hoja, asi que 
			//pregunto despues por si soy hoja
			Dash_Structures::DBTree<int>::iterator l = p.left_child();
			Dash_Structures::DBTree<int>::iterator r = p.right_child();

			int aux;
			aux = Bremove_leaf( T , l , min_leaf );

			*p += aux;

			aux = Bremove_leaf( T , r , min_leaf );

			*p += aux;

			//IMPORTENTE, notar que como ya que estube posiblemente borrando hijos, capaz que ahora soy una hoja

				bool is_leaf = ( (p.left_child() == T.end() ) && (p.right_child() == T.end() ) );
			if( is_leaf ){//Si es hoja, y tambien es menor que min_leaf, la borro y le devuelvo 
				//su valor par qeu lo sume su padre
				if( *p < min_leaf ){
					int aux = *p;
					p = T.erase( p );//no es nesesaria la asignacion, pero mejor simepre hacerla porque si en un caso
					//donde se nesesite no se la hace se muere de una forma brutal
					return (aux);
					}

				return 0;//si es mayor, enotnces no hago nada

				}

			//como no es hoja returno 0
			return 0;


		}

		//WRAPPER
	//es para un arbol binario, lo que hace es recorrer las hojasde arbol, y si alguna es menorqe elparametro min_leaf
	//luego borro la hoja y le sumo su valor a el padre.
	int Bremove_leaf( Dash_Structures::DBTree<int> & T , int min_leaf){
		
			return Bremove_leaf( T, T.begin() , min_leaf );

		}

	//Devuelve en la variable h la altura que le corresponde a un arbol binario
	void Bheight( Dash_Structures::DBTree<int> & T , Dash_Structures::DBTree<int>::iterator p , int& h ){

		if( p == T.end() ){
			h = -1;//si entro aca es proque la raiz era lamda, entonces devuelvo un bolazo
			return;
			}

		Dash_Structures::DBTree<int>::iterator l = p.left_child();
		Dash_Structures::DBTree<int>::iterator r = p.right_child();
		
		bool is_leaf = ( ( l == T.end() ) && ( r == T.end() ) );//si es que es una hoja
		if( is_leaf ){
			return;//salgo directamente, y no me afecta la altura, vendria a compensar que la raiz no se cuenta
			//en la altura
			}

		//si no es una hoja entonces me fijo cual es la altura de los hijos

		int left_h = 0;
		int right_h = 0;

		Bheight( T, l , left_h );
		Bheight( T, r , right_h );

		if( left_h > right_h ){//asigno la altura mayor incrementada en 1
		
			h = left_h + 1;
			return;

			}else{

				h= right_h + 1;
				return;
			}

		}

		//WRAPPER
	//Devuelve en la variable h la altura que le corresponde a un arbol binario
	void Bheight( Dash_Structures::DBTree<int> & T , int& h ){
	
		return Bheight( T, T.begin() , h );
		return;

		}

	void height( Dash_Structures::DTree<int> & T , Dash_Structures::DTree<int>::iterator p , int& h ){

		if( p == T.end() ){
			h = -1;//devuelvo un bolazo
			return;
			}

		Dash_Structures::DTree<int>::iterator c = p.lchild();

			bool is_leaf = ( c == T.end() );
		if( is_leaf ){
			h=0;//si es una hoja retorno 0, para compensar que en la altura la raiz no se cuenta,
			//es decir que no suma en realidad
			return;
			}


		//como no es ni lamda ni una hoja, entonces me fijo en sus hijos

			int max_h =0;
		while( c != T.end() ){
			int aux = 0;
			height( T , c++, aux );

			if( aux > max_h )
				max_h = aux;

			}

			//entonces la altura final sera la altura de sus hijos mas la raiz,
			//notar que aca se cuenta la raiz, porque no se conto la hoja... y asi se compenso
			h = max_h + 1;
			return;

		}

	void height( Dash_Structures::DTree<int> & T , int& h ){

		height( T , T.begin(), h );
		return;

		}

	//Dice si A < B, para arboles binarios, si lo es tira verdadero, si no lo es tira falso
	//el criterio es
	//
	//				-1) a < b					a				b
	//		A < B	-2) Ai < Bi				-----------		-----------
	//				-3) Ad < Bd				|		  |		|		  |
	//										Ai		  Ad	Bi		  Bd
	//Donde tiene ese roden los criterios
	bool menor( Dash_Structures::DBTree<int> & A , Dash_Structures::DBTree<int>::iterator a , Dash_Structures::DBTree<int> & B, 
		Dash_Structures::DBTree<int>::iterator b ){

			if( ( a == A.end() ) ||  ( b == B.end() ) ){//si es que alguno es end..
				//yo despue slosdesreferencia, entonces si uno es end tengo que manejarlo aca dentro si o si
				//hay que contemplar cual posibilidad es y hacer un return

		if( ( a == A.end() ) && ( b != B.end() ) )//criterio basico
			return true;

		if( ( a != A.end() ) && ( b == B.end() ) )//criterio basico
			return false;

		if( ( a == A.end() ) && ( b == B.end() ) )//criterio basico
			return false;

			//Ya estoy seguro qeu logicamente contemple todas las posibilidades
			//a puede ser end o no, b puede ser end o no, estas son todas
			// luego 2*2 = 4  , en la entrada ya me asegure que uno es end
			//osea que != end y != end en los dos queda descartado
			//luego me quedan 3 posibilidadesuqe son las tres que se
			//verifican arriba

				}

		//criterio 1
		if( (*a) < (*b) )
			return true;

		//criterio 2
		if ( menor( A, a.left_child() , B , b.left_child() ) )
			return true;

		//criterio 3
		if( menor( A, a.right_child() , B , b.right_child() ) )
			return true;

		//sino cumple con ningun criterio, luego no es menor
		//puede llegar a ser igual o mayor, nose cual
		return false;

		}

			//WRAPPER
		//hace lo que explica la funcion de arriba
		bool menor( Dash_Structures::DBTree<int> & A , Dash_Structures::DBTree<int> & B ){

			return menor( A , A.begin() , B , B.begin() );

			}

		//lista los nodos por nivel, de un arbol orientado prdenado, es decir primero todos los nodos
		//del nivel 0, despues los del nivel 1, ect
		//											IMPORTANTE: USA CLASES DE LA STL, PORQUE LAS MIAS TENIAN
		//											UN ERROR QUE NO ARREGLE, SE TIENEN QUE INCLUIR LIST Y MAP FUERA 
		//											DE ESTE .H, EN EL ESPAICO DE NOMBRES GLOBAL
		void list_nodes_per_level( Dash_Structures::DTree<int> & T , Dash_Structures::DTree<int>::iterator p,
			int level , std::map<int , std::list<int> > & Node_Map ){

				if( p == T.end() )
					return;

				( Node_Map[level] ).push_back( *p );//agrego el nodo al nivel

				Dash_Structures::DTree<int>::iterator c = p.lchild();

				while( c != T.end() ){
					list_nodes_per_level( T , c++ , level + 1 , Node_Map );
										
					}
				return;

			}

			void list_nodes_per_level( Dash_Structures::DTree<int> & T ,
				 std::map<int , std::list<int> > & Node_Map ){

				list_nodes_per_level( T , T.begin() , 0 , Node_Map );
				return;

					}


	}//fin de AED_Parciales




	namespace BTree_Algorithms{

#ifdef NOT_NAMESPACE_DASH_STRUCTURES_IN_ALL_CPPS
	//using namespace Tree_ADT;
#endif

//para ver en notacion lisp arboles binarios
	void Lisp_print( Dash_Structures::DBTree<int>& T, Dash_Structures::DBTree<int>::iterator p, std::string& str){

	//Los nodos vacios se marcan con .
	if( p == T.end() ){
		str += ". ";
		return;
		}

	Dash_Structures::DBTree<int>::iterator l = p.left_child();
	Dash_Structures::DBTree<int>::iterator r = p.right_child();

	//si es que es una hoja entonces almaceno el valor, y no va la estructura ( .. ) de 
	//padre, ya uqe seria redundante poner ( val . . )
	bool is_leaf = ( ( l == T.end() ) && ( r == T.end() ) );
	if( is_leaf ){
		char* buf = new char[10];
		itoa(*p,buf,10);
		std::string aux = buf;
		aux += " ";

		str += aux ;

		}else{//si es que no es hoja tiene almenos 1 hijo
			//este se analizara, de ser alguno end, se leera como un .


	std::string aux = "( ";	
	char* buf = new char[10];
	itoa(*p,buf,10);
	aux += buf;
	aux += " ";
	
	str += aux;
	
	//llamadas recursivas para los hijos
		Lisp_print( T, l, str);
		
		Lisp_print( T, r, str);

	str += ") ";

		}
	
	return;
	}

//funcion wrapper
void Lisp_print(Dash_Structures::DBTree<int>& T, std::string& str ){

	Lisp_print( T , T.begin() , str ) ;
	
	}

	}//Fin de BTree_Algorithms

namespace Sort_Algorithms{

		template<class C, class func>
	typename C::iterator partition( const typename C::iterator & first , const typename C::iterator & last , func comp , 
		typename C::value_type _pivot ){
		
			//voy avanzando por izquierda y por derecha, avanzan hacia un choque mutuo!
			//cuando un elemnto clasifica en el grupo izquierdo avanza left
			int left=0;
			//cuando un elemento clasifica en el grupo rigth retrocede rigth
			int rigth=1;

			while(true){
				//hago un intercambio, si no me sirve en la proxima vuelta
				//re armo como estaba antes
				//Notar que siempre un elemnto se mueve porque de dos valores: a y b
				// o a<pivote o a>=pivote   lo mismo para b asi qeu alguno siempre avanza o los dos
				typename C::value_type aux = *(first+left);
				*(first+left) = *(last-rigth);
				*(last-rigth) = aux;

					//primero avanzo, despues verifico salida, porque despues de avanzar se pueden chocar y en la entrada siguiente intercambiar 
					//elementos y entrar en un loop infinito

				//avanze, y retrocezo, se mueven al choque
				if( comp( *(first+left) , _pivot ) )
					left++;
				if( !comp( *(last-rigth) , _pivot ) )
					rigth++;

								//si se pasaron o estan iguales termine
				if( (last-rigth) <= (first+left) )//termina en el ultimo que clasifico en una particion
					return (!comp(*(last-rigth),_pivot))?(last-rigth):(last-rigth+1);//si clasifica este ultimo dentro
																					 //de la particion es este el comienzo


				}//Fin del while(true)

		}

		template<class C, class func>
	typename C::value_type pivot( const typename C::iterator & first , const typename C::iterator & last , func comp ){

			C::value_type a = *first;
			C::value_type b;

			for(int i=1 ;i < (last-first); i++){
				//si  !(a<b) && !(b<a) luego a==b
				if( !comp(a , *(first+i) ) && !comp( *(first+i) , a) )
					continue;
				else{//si encuentro alguno diferente termino 
					b= *(first+i);
					//devuelvo el mas grande
					return ( (a<b)? b:a);
					}
				}

		}

		template<class C, class func>
	bool at_leat_two( const typename C::iterator & first , const typename C::iterator & last , func comp ){

			for( int i=1; i<(last-first) ; i++ ){
				for( int j=0; j< i ; j++ ){
					//si  !(a<b) && !(b<a) luego a==b
					if( !comp( *(first+j) , *(first+i) ) && !comp( *(first+i) , *(first+j) ) ){
						continue;
					}else{//si es que encuantro almenos uno distinto a otro luego ya hay 2 diferentes, y salgo
						return true;
						}

					}
				}

			return false;

		}

		template<class C>
	void ver_proceso1(const typename C::iterator & first , const typename C::iterator & last,
		const typename C::value_type _pivot ){

			std::cerr<<"El vector a ordenar en esta iteracion es:\n";
			typename C::iterator it=first;
			std::cerr<<"(";
			while( it != (last-1) ){
				std::cerr<<*(it++)<<",";
				}std::cerr<<*(it)<<")\n";
			std::cerr<<"El pivote es: "<< _pivot;

			return;

		}

		template<class C>
	void ver_proceso2(const typename C::iterator & first , const typename C::iterator & last , const typename
		C::iterator & middle){
	
			std::cerr<<"\nParticion izquierda:\n";
			typename C::iterator it=first;
			while(  it != middle )
					std::cerr<<*(it++)<<" ";
			std::cerr<<"\nParticion derecha:\n";
			while( it != last )
				std::cerr<<*(it++)<<" ";
			std::cerr<<"\n\n";

			getchar();
			
		}


	//Su estrategia se basa en dividir para vencer. Logra timepos generalmente de O( n*ln(n) ). Es in-place
	//pero esto depende de las estrategias de eleccion del pivote principalmente
	//No es estable almenos que se utilize un algoritmo de particionamiento estable, aca se uso uno inestable
	//Sus pasos BASICOS son:
	//I) Verificar salida en que si no hay elementos para ordenar o solo hay 1 elemento sale(por ser 1 ya
	//   esta ordenado)
	//II) Se elege un pivote que sera un valor, lo ideal es que sea el valor que una vez odenado la estructura
	//    este en la mediana, osea en el medio del arreglo o lo mas cercano posible
	//III) Se particiona la estructura en dos grupos los menores que pivote y en los mayores o iguales a pivote
    //	                                < pivote        >= pivote
	//		Es importante que el pivote este en la mediana para que los dos grupos sean de tamaños parecidos
	//		lo que hace que el algoritmo solucione primero
	//IV)  LLama Recursivamente a quick_sort de las 2 particiones logrando qeu las dos esten ordenadas
	//						TERMINA CON EL VECTOR ORDENADO COMPLETAMENTE
	//NOTA: LOS MOVIMIENTOS DE ELEMENTOSSE HACEN IN-PLACE, OSEA QUE NO OCUPAN MAS MEMORIA Y QUE NO
	//      SE USAN ESTRUCTURAS ADICIONALES
	//
	//Quick-Sort require que el contenedor posea iteradores random-access
		template< class C , class func>
	void quick_sort( const typename C::iterator & first , const typename C::iterator & last , func comp ){

				//I)

			//No hay que hacer nada si pasan dos cosas:
			//1) Solo hay 1 elemento, el cual por ser unico esta ordenado. No hay elementos.
			//   O last es menor a first
			//2) Si es que no hay almenos 2 valores diferentes en la estructura.
			//   No se ejecuta nada porque el resto es tribial ya que si solo hay un valor(repetido varias veces)
			//   luego la estructura ya esta ordenado
			if( ( (last-first)<=1 )  ||  !at_leat_two<C>(first , last , comp) )
				return;

				//Certezas: ya se que hay alemnos 2 elementos en la estructura y que almenos 2 son diferentes

			//Si es que hay muy pocos elementos, aca considero pocos 10 o menos
			//Llama a un metodo leto de ordenamiento ya que apesar de ser de orden mayor lo hara 
			//mas rapido por ser menos 'vueltero'
			if( (last-first) <= 10 ){
				//bubble_sort(first,last,comp);
				}

				//II)
			typename C::value_type _pivot = pivot<C>( first, last, comp );

					//muestra el proceso de ordenamiento detallaod y lindo
					//ver_proceso1<C>(first,last,_pivot);
				//III)
			typename C::iterator middle = partition<C>( first, last, comp, _pivot );
					
					//muestra el proceso de ordenamiento detallaod y lindo
					//ver_proceso2<C>(first,last,middle);

				//IV)

			//Ordena [first,middle)
			quick_sort<C>( first, middle, comp );
			//Ordena [middle,last)
			quick_sort<C>( middle, last, comp );

				//Certezas: Ya ordena los rangos fist-middle y middle-last
				//luego por ser estas dos partes toda la estructura, ya ordene todo

		}


	//Su estrategia es dividir para vener. Recibe el contenedor a ordenar, y la funcion de comparacion.
	//Logra timepos generalmente de O( n*ln(n) ). Es in-place, utiliza contenedor auxiliar pero a medida 
	//que ingresa en este borra del anterior. Esta implementacion es no-estable, pero se la podria hacer
	//estable si se modifica el particionamiento
	//Solo requiere forward-iterators y de accesso. Srive por esto para listas, puede funcionar para vectores
	//pero esta implementacion implace sera MUY LENTA, ya que el borrar en el medio es muy lento.
	//Si se implementa no-in-place serviria para vectores, pero ocuparia mas memoria aunque sea del mismo orden
	//que quick-sort.
	//Su procedimiento BASICO es:
	//I) Se verifica que si hay solo 0 o 1 elemento ya esta ordenado y sale
	//II) Dividir la estructura en dos estructuras del mismo tamaño o similar
	//III) Se llama recursivamente a merge-sort de las dos estructuras
	//IV) Luego por recursividd ya setiene ordenadas las partes (porque divide hasta que solo
	//    halla un elemento, y eso simepre esta ordenado). Se mergea(fusiona) las estructuras
	//    de forma ordenada
	//
	//Merge-Sort require que el contenedor posea iteradores forward y access
		template<class C,class func>
	void merge_sort( C & L , func comp ){

		//si posee ningun elemento o 1 elemento sale
			//I)
		if( L.empty() || (++L.begin() == L.end()) )
			return;

			//Certezas: ya se que hay almenos 2 elementos en la estructura

		//barajamento par/impar     no-estable pero se podria modificar
			//II)
		C L1;
		C L2;
		bool flag=true;
		while( !L.empty() ){
			if( flag ){
				L1.insert( L1.end() , *L.begin() );
				L.erase( L.begin() );
				}else{
				L2.insert( L2.end() , *L.begin() );
				L.erase( L.begin() );
				}

			flag=!flag;

			}

		//III)
	//ordeno por recursividad la primera particion
	merge_sort( L1 , comp );
	//ordeno por recursividad la segunda particion
	merge_sort( L2 , comp );


	//IV)
	while( !L1.empty() && !L2.empty() ){

		if( comp( *L1.begin() , *L2.begin() ) ){
			L.insert( L.end() , *L1.begin() );
			L1.erase( L1.begin() );
			}else{
			L.insert( L.end() , *L2.begin() );
			L2.erase( L2.begin() );
			}
		}

	while( !L1.empty() ){
			L.insert( L.end() , *L1.begin() );
			L1.erase( L1.begin() );
		}

	while( !L2.empty() ){
			L.insert( L.end() , *L2.begin() );
			L2.erase( L2.begin() );
		}

	return;

		}

	}//Fin de Sort_Algorithms

#endif