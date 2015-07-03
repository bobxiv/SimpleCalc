#include <vector>
#include <set>
#include <map>
#include <list>
#include <algorithm>


namespace AED_Parciales{//usando stl


			//Se ingresa un grafo no-ponderado, no-dirijido, simple G, donde el vector determina 
			//que numero de nodo es del que se habla, y cada uno de estos nodos contiene 
			//un setde las adyacencias de cada nodo. Es decir:
			//			V(los nodos)	ady(las adyacencias)         Osea:
			//			0			    1 2                           1------|
			//			1				0 2                           |      2---
			//			2			    0 1 3                         0------|   |
			//          3				2                                        3
			//Ademas se ingresa un nodo x. Y una lista de los nodos por niveles, fiscriminando de la siguente forma
			//I) En L[0]=x ya que se empieza a contar las capas desde el nodo qeu se ingresa
			//II) En L[1]= {nodos adyacentes a x} 
			//III) En l>1 estaran los nodos adyacentes a (l-1) tal que no esten ni en (l-2) ni en (l-1)
			//     Notar que solo verificamos ahi y no en 0-(l-1) ya que para poder 'tocar' l-3 debe si o si
			//     tocar l-2
			//Esto logra que en L haya una particion en capas(layers) arrancando desde x
			//Tal que desde x para llegar a un nodo en la capa l, hay una ruta de longitud l
			//             En el ejemplo de arriba, arrancando desde x=0 las capas serian:
			//									L              Nodos
			//									0              0
			//									1              1 2
			//									2              3
			void mklayer( const std::vector<std::set<int>>& G, int x , std::vector<std::set<int>>& L ){
				L.push_back( std::set<int>() );
				L[0].insert( x );

				L.push_back( std::set<int>( G[x] ) );

				int i=1;

				//mientras no este vacio el ultimo nivel agregado
				//si lo estubiese ya no me podria 'expandir' por nuevos niveles
				while( !L[i].empty() ){

					//el nuevo nivel
					L.push_back(std::set<int>());

					//iterador a los nodos del ultimo nivel completo
					std::set<int>::iterator node = L[i].begin();

					//mientras haya nodos en la ultima capa sin recorrer
					while( node != L[i].end() ){
							//cargo en ady los nodos adyacentes a el nodo node de esta iteracion
						const std::set<int>& ady = G[*node];
						//iterador a los nodos adyacentes a el nodo de esta iteracion
						std::set<int>::const_iterator near=ady.begin();

						while( near != ady.end() ){
								//me fijo en l-1 si esta, si esta este nodo NO es de una capa exterior
							if( L[i].find( *near ) != L[i].end() ){//SI ESTA?
								near++;
								continue;
								}
								//me fijo en l-2 si esta, si esta este nodo NO es de una capa exterior
							if( L[i-1].find( *near ) != L[i-1].end() ){//SI ESTA?
								near++;
								continue;
								}


							L[i+1].insert( *near );
							near++;

							}//fin de las iteraciones por adyacencia

						//paso al siguiente nodo de la ultima capa completa
						node++;
						
						}//fin de las iteraciones por nodos del ultimo nivel

					//incremento el nivel de nodos
					i++;

					}//fin de las iteraciones por niveles, termina cuando en el ultimo nivel que se busco no se
					 //encontro ningun nodo para agregar

				//saco el ultimonivelque estara vacio
				L.pop_back();
				
				return;

				}





			int includes_all( const std::vector<std::set<int>>& Vs ){


				return 7;

				}


			
void simetric_diff_1( std::list< std::set<int> > & L , std::set<int>& S ){

	std::list< std::set<int> >::iterator it= L.begin();
	while( it != L.end() ){//iteracion por todos los conjuntos de la lista

		std::list< std::set<int> >::iterator ver= L.begin();
		
			std::set<int> aux=*it;//aux es el conjunto completo que se analiza y se le va sacando las partes
			//que chocan con otros conjuntos
		while( ver != L.end() ){//recorrido por los demas conjuntos de la lista
			if( ver == it ){
				ver++;
				continue;//si son el mismo la operacionhara anda asi que la salteo
				}

			//tmp = Ai - Bj
			std::set<int> tmp;
			std::set_difference( (*it).begin() , (*it).end() ,
				(*ver).begin() , (*ver).end() , std::inserter( tmp , tmp.begin() ) );

			//aux = tmp2 int tmp    ---->    aux = aux int tmp    --->    aux = aux int (Ai-Bj)
			std::set<int> tmp2=aux;
			aux.clear();//limpio aux
			std::set_intersection(tmp.begin(), tmp.end(), tmp2.begin() , tmp2.end() ,
				std::inserter( aux , aux.begin() ) );

			ver++;

			}//fin while
		//aux aca ya tiene lo que esta en un conjuto y no esta en los demas, esto lo sumo a S

			//S = temp U aux    --->    S = S U aux   --->   S = S U Vtodo i( aux int Vtodo j(Ai - Bj) )
			//                                                  con aux en un comienzo igual a Ai
		std::set<int> temp = S;
		S.clear();//limpio S
		std::set_union( temp.begin() , temp.end() , 
			aux.begin() , aux.end() , std::inserter( S , S.begin() ) );

		it++;
	
		}//fin while

	}

//Se le ingresa un grafo G, y se selecciona un x, nodo del grafo G, para comenzar el 
//algoritmo. Luego larga por W, el grupo de todos los nodos connexon a x
//Es relativamente similar a mklayer
// F es la frontera de los nodos que se vana agregando
// Q son los vecinos de F
// W tiene los conexion a x
// G tiene todo el grafo, sus partes conexas y tambien no conexas
void connected_to(std::map<int,std::set<int>> &G, int x , std::set<int>& W){

W.insert(x);
std::set<int> F;

//----------------------------------------------------------
F=G[x];									//comienzo no bueno
//----------------------------------------------------------
//F.insert(x);

while( !F.empty() ){//itero por niveles de F

	std::set<int>::iterator p = F.begin();
	std::set<int> Q;

	while( p != F.end() ){//itero por las adyacencias de F

		//std::set<int>::iterator it= G[*p].begin();

		//while( it != G[*p].end() ){

			std::set<int> tmp;
			//Esto lo rompe
		//	std::set_union(*it.begin() , *it.end(),
		//		Q.begin(), Q.end() , std::inserter(tmp, tmp.begin()) );
			//Hasta aca lo que rompe todo
			std::set_union(G[*p].begin() , G[*p].end(),
				Q.begin(), Q.end() , std::inserter(tmp, tmp.begin()) );

			Q=tmp;
			//it++;

			//}
		p++;

		}//fin del while por adyacencias de forntera

	//sale Q conteniendo todos las adyacencias de F, las qeu van 'hacia afuera' y 'hacia dentro'

	std::set<int> tmp2;
	//    Fnovo = Q - W
	std::set_difference(Q.begin() , Q.end() , W.begin() , W.end() ,
		std::inserter(tmp2,tmp2.begin()) );

	//----------------------------------------------------------
	std::set<int> tmp3;
	//    arregla un comienzo no bueno
	std::set_union(F.begin() , F.end() , W.begin() , W.end() ,
		std::inserter(tmp3,tmp3.begin()) );
	W=tmp3;
	//----------------------------------------------------------

	F=tmp2;

	tmp2.clear();
	//	  Wnovo = W U Fnovo
	std::set_union( W.begin() , W.end() , F.begin() , F.end() ,
		std::inserter(tmp2,tmp2.begin()) );

	W=tmp2;

	}//fin del while por niveles de frontera


	}


//La funcion se le ingresa un conjunto S con elementos y una funcion de comparacion
//y el algoritmo larga por la salida en L una lista con todas las 'clases de equivalencia'
//En cada una se ingresan los valores que son equivalentes segun la relacion de equivalencia
void eq_class( std::set<int>& S , std::list<std::set<int>>& L , bool(*comp)(int,int)){

	std::vector<int> V;
	std::set<int>::iterator it = S.begin();
	while( it != S.end() ){
	
		V.push_back(*it);
		it++;

		}

	std::sort( V.begin() , V.end() , comp );

	L.push_back(std::set<int>());

	int prev = V[0];

	std::list<std::set<int>>::iterator p = L.begin();
	(*p).insert(prev);
	for( int i=1; i < V.size() ;i++ ){

		if( !comp(prev , V[i]) && !comp(V[i] , prev) ){

			(*p).insert(V[i]);
			
			}else{

				L.push_back(std::set<int>());
				p++;
				(*p).insert(V[i]);

				prev = V[i];



			}

		}//fin del for



	}


}//fin de AED_Parciales

