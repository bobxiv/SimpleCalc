//Un arbol Binario
#pragma once

#ifndef DASH_BTREE

#define DASH_BTREE

#include "CommonTypes.h"

#include "Utility.h"


#ifndef NOT_NAMESPACE_DASH_STRUCTURES_IN_ALL_CPPS
_BEGIN_DASH_STRUCTURES_NAMESPACE
#endif


template<class _Tp>
class DBTree;
template<class _Tp>
class _BTree_Iterator;
template<class _Tp>
class _DBTree_Node;

class _DBTree_Node_Base{

	protected:
	_DBTree_Node_Base* right_child;
	_DBTree_Node_Base* left_child;

	_DBTree_Node_Base(_DBTree_Node_Base* _right_child , _DBTree_Node_Base* _left_child):
	right_child( _right_child ), left_child( _left_child ) {}
	

	};

template<class _Tp>
class _DBTree_Node: public _DBTree_Node_Base{

	friend class DBTree<_Tp>;
	friend class _BTree_Iterator<_Tp>;

	_Tp data;

	_DBTree_Node(): data( _Tp() ) , _DBTree_Node_Base(NULL,NULL) {}

	};

template<class _Tp> 
class _BTree_Iterator{

	friend class DBTree<_Tp>;

public:
		enum side_type{ Right , Left , None };

private:

	typedef _DBTree_Node<_Tp> _Node;

	_Node* ptr;
	_Node* father;

	side_type Side;

	_BTree_Iterator( _Node* _ptr, _Node* _father , side_type _Side): ptr(_ptr) , father(_father) , Side(_Side) {}

public:

	_BTree_Iterator(): ptr(NULL), father(NULL), Side(side_type::None) {}

	_BTree_Iterator(_BTree_Iterator& _B): ptr(_B.ptr) , father(_B.father) , Side(_B.Side){}

	_BTree_Iterator& operator=(_BTree_Iterator _B) {
		this->ptr = _B.ptr;
		this->father = _B.father;
		this->Side = _B.Side;
		return (*this);
		}

	_Tp& operator*(){
		return (*ptr).data;
		}
	_Tp* operator->(){
		return &( (*ptr).data );
		}

	_BTree_Iterator right_child(){
		return _BTree_Iterator( static_cast<_Node*>( ptr->right_child ) , ptr , side_type::Right );
		}

	_BTree_Iterator left_child(){
		return _BTree_Iterator( static_cast<_Node*>( ptr->left_child ) , ptr , side_type::Left );
		}

	bool operator==(_BTree_Iterator& _B){
		return (this->ptr == _B.ptr);
		}

	bool operator!=(_BTree_Iterator& _B ){
		return (this->ptr != _B.ptr);
		}

	};


template<class _Tp>
class DBTree{

public:

	typedef _Tp value_type;
	typedef _BTree_Iterator<_Tp> iterator;
	typedef const _BTree_Iterator<_Tp> const_iterator;
	typedef _Tp* pointer;
	typedef const _Tp* const_pointer;
	typedef _Tp& reference;
	typedef const _Tp& const_reference;
	typedef _DBTree_Node<_Tp> _Node;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;

private:

	_Node Header;

public:

	DBTree(){
		Header.data = value_type();
		Header.left_child = NULL;
		Header.right_child = NULL;
		}

	DBTree(DBTree& _B){
		if( &_B != this ){
		Header.data = value_type();
		Header.left_child = NULL;
		Header.right_child = NULL;

		if( _B.begin() != _B.end() )
		Copy( iterator( (_Node*) Header.left_child, &Header, iterator::side_type::Left),
			_B , 
			iterator( _B.begin() ) );

			}

		}

	~DBTree(){
		this->clear();
		}

	DBTree& operator=( DBTree& _B){
		if( &_B != this ){

			this->clear();

			Copy( this->begin(),
				_B , 
				_B.begin()  );

			}

		return (*this);

		}

	iterator begin(){
		return iterator( static_cast<_Node*>( Header.left_child ) , &Header , iterator::side_type::Left );
		}

	iterator end(){
		return iterator();
		}

	iterator insert(iterator _p, value_type _val){
		//solo se puede insertar en posiciones no referenciables, hacerlo en una
		//referenciable es un error y provoca memory leak, por eso esta el assert
		assert( _p == this->end() );

		_Node* novo = new _Node();
		novo->data = _val;
		
		_p.ptr = novo;

		if( _p.Side == iterator::side_type::Right ){
		_p.father->right_child = novo;
			}else{
			_p.father->left_child = novo;
			}

		return _p;
		}

	iterator erase(iterator _p){
		if( _p == this->end() ) return iterator();

		erase( _p.left_child() );
		erase( _p.right_child() );

		delete _p.ptr;
		_p.ptr = NULL;

		if( _p.Side == iterator::side_type::Right ){
			_p.father->right_child = NULL;
			}else{
				_p.father->left_child = NULL;
			}

		return _p;
		}

	iterator splice(iterator from, iterator to){

		if( from == this->end() ) return to;


		if( from.Side == iterator::side_type::Right ){
		from.father->right_child = NULL;
			}else{
			from.father->left_child = NULL;
			}

		to.ptr = from.ptr;

		if( to.Side == iterator::side_type::Right ){
		to.father->right_child = from.ptr;
			}else{
			to.father->left_child = from.ptr;
			}

		from.ptr =NULL;

		return to;
		}

	void clear(){
		erase( this->begin() );
		}

	iterator find(iterator _p, value_type _val){
		if( ( _p == this->end() ) || ( (*_p) == _val ) )
			return _p;

		iterator r = _p.right_child(), l=_p.left_child()
			, aux;

		aux = find( l , _val );

		if( aux != this->end() )
			return aux;

		aux = find( r, _val );

		if( aux != this->end() )
			return aux;

		}

	//funcion wrapper
	iterator find( value_type _val ){
		return find( this->begin() , _val );
		}

	//copia de otro arbol, una deep copy, aca _a debe ser no referenciable
	//y b debe ser referenciable
	void Copy( iterator _a , DBTree& _B , iterator _b){
		_a = this->insert( _a, (*_b) );

		iterator aux = _b.left_child();

		if( aux != _B.end() )
			Copy( _a.left_child() , _B , aux );

		aux = _b.right_child();

		if( aux != _B.end() )
			Copy( _a.right_child() , _B , aux );

		}

	//para ver el arbol en notacion lisp de un nodo en adelante
	void Lisp_print(iterator p, std::string& _str){
			//Los nodos vacios se marcan con .
	if( p == this->end() ){
		_str += ". ";
		return;
		}

	iterator l = p.left_child();
	iterator r = p.right_child();

	//si es que es una hoja entonces almaceno el valor, y no va la estructura ( .. ) de 
	//padre, ya uqe seria redundante poner ( val . . )
	//								ANDA CON ARBOLES DE NUMEROS
	bool is_leaf = ( ( l == this->end() ) && ( r == this->end() ) );
	if( is_leaf ){
		char* buf = new char[10];
		itoa(*p,buf,10);
		std::string aux = buf;
		aux += " ";

		_str += aux ;

		}else{//si es que no es hoja tiene almenos 1 hijo
			//este se analizara, de ser alguno end, se leera como un .


	std::string aux = "( ";	
	char* buf = new char[10];
	itoa(*p,buf,10);
	aux += buf;
	aux += " ";
	
	_str += aux;
	
	//llamadas recursivas para los hijos
		Lisp_print( l, _str);
		
		Lisp_print( r, _str);

	_str += ") ";

		}

	return;

		}

	//para ver el arbol en notacion lisp desde el comienzo
	//								ANDA CON ARBOLES DE NUMEROS
	void Lisp_print( std::string& _str ){

		Lisp_print( this->begin() , _str );

		}

	//Saca por el string el arbol en orden previo desde un nodo al que apunta el iterador
	//								ANDA CON ARBOLES DE NUMEROS
	void prev_ord( iterator _p , std::string& _str ){

		if( _p == this->end() )//si entro en un nodo vacio, no quiero que modifique la salida
			return;

		if( _str.length() != 0 ){//la primera vez no quiero una coma primero, sino queda feo
		_str += ",";//como es preorden primero proceso el padre
			}
		char* _buf = new char[10];
		itoa( (*_p) , _buf , 10);
		_str += _buf;

		iterator _l = _p.left_child();//llamo a procesar los hijos
		iterator _r = _p.right_child();

			prev_ord( _l , _str );
			prev_ord( _r , _str );
		

		return;

		}

	//Saca por el string el arbol en orden previo, desde la raiz
	//								ANDA CON ARBOLES DE NUMEROS
	void prev_ord( std::string& _str ){

		prev_ord( this->begin() , _str );
		return;

		}

	//Saca por el string el arbol en orden post desde un nodo al que apunta el iterador
	//								ANDA CON ARBOLES DE NUMEROS
	void post_ord( iterator _p , std::string& _str ){

		if( _p == this->end() )//si entro en un nodo vacio, no quiero que modifique la salida
			return;

		iterator _l = _p.left_child();//llamo a procesar los hijos
		iterator _r = _p.right_child();

			post_ord( _l , _str );
			post_ord( _r , _str );

		if( _str.length() != 0 ){//la primera vez no quiero una coma primero, sino queda feo
		_str += ",";//como es postorden a lo ultimo proceso los nodos
			}
		char* _buf = new char[10];
		itoa( (*_p) , _buf , 10);
		_str += _buf;
		

		return;

		}

	//Saca por el string el arbol en orden post, desde la raiz
	//								ANDA CON ARBOLES DE NUMEROS
	void post_ord( std::string& _str ){

		post_ord( this->begin() , _str );
		return;

		}

	//Saca por el string el arbol en orden entre desde un nodo al que apunta el iterador
	//								ANDA CON ARBOLES DE NUMEROS
	void entre_ord( iterator _p , std::string& _str ){

		if( _p == this->end() )//si entro en un nodo vacio, no quiero que modifique la salida
			return;

		iterator _l = _p.left_child();//llamo a procesar el hijo izquierdo


			entre_ord( _l , _str );

		if( _str.length() != 0 ){//la primera vez no quiero una coma primero, sino queda feo
		_str += ",";//como es entreorden proceso el nodo en medio de las llamadas a los 2 hijos
			}
		char* _buf = new char[10];
		itoa( (*_p) , _buf , 10);
		_str += _buf;


		iterator _r = _p.right_child();//llamo a procesar el hijo derecho

			entre_ord( _r , _str );

		return;

		}

	//Saca por el string el arbol en orden entre, desde la raiz
	//								ANDA CON ARBOLES DE NUMEROS
	void entre_ord( std::string& _str ){

		entre_ord( this->begin() , _str );
		return;

		}


		};




#ifndef NOT_NAMESPACE_DASH_STRUCTURES_IN_ALL_CPPS
_END_DASH_STRUCTURES_NAMESPACE
#endif



#endif