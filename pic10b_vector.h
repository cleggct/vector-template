#include <iostream>   // std::ostream, std::cout
#include <string>

namespace Pic10b{

	template <typename T>
    class vector{
      private:
        T* the_data; //change the type from double generic T
        size_t the_size;
        size_t the_capacity;

        static const int INIT_CAP = 10;


      public:
        // The big 4 
        vector();
        vector( const vector<T>& ); //now we are taking generic vectors, not double vectors
        vector& operator=( const vector<T>& );
        ~vector();

        // Other members [public]
        bool empty() const;
        size_t size() const;
        size_t capacity() const;
        T front() const; //return types must also be changed from double to generic T
        T back() const; 
        T at( size_t index ) const;
        T& operator[]( size_t index );
        T operator[]( size_t index ) const; 
		vector<T>& operator+=(const vector<T>& rhs); //add operator+= as a member function
		vector<T> operator*(const T& rhs); //also add one of the operator* as a member function
        void dump_data_to( std::ostream& out ) const;
        void dump_data() const;
        void push_back( T new_value ); //now use generic T for new values
        void pop_back();


      private:
        //Other members [private]
        void reserve( size_t new_capacity );

    }; // end Pic10b::vector


    /** ************************* THE BIG 4 ************************* **/
	template<typename T>
    vector<T>::vector() 
      : the_data(nullptr), the_size(0), the_capacity(INIT_CAP) {
		std::cout << "xxx: Default constructor...\n"; //add a statement for when the default constructor is called
        the_data = new T[the_capacity]; //use arrays of generic T instead of double
    }

	template<typename T>
    vector<T>::vector( const vector<T>& source )
      : the_data(nullptr), the_size(source.the_size), 
        the_capacity(source.the_capacity) {

        the_data = new T[the_capacity]; //array of generic T, not double

        // Deep copy of internal array
        for ( int i = 0 ; i < the_size ; ++i ){
            the_data[i] = source.the_data[i];
        }
		std::cout << "xxx: Copy constructor...\n"; //add a statement for when the copy constructor is called
    }

	template<typename T>
    vector<T>& vector<T>::operator=( const vector<T>& rhs ) {
        if ( this != &rhs ) {     // Self-assignment?
            // Release old memory and request more 
            delete[] the_data;
            the_data = new T[rhs.the_capacity];

            // Shallow copy non-pointers
            the_size = rhs.the_size;
            the_capacity = rhs.the_capacity;

            // Deep copy internal array
            for ( int i = 0 ; i < the_size ; ++i )
                the_data[i] = rhs.the_data[i];
        }
		std::cout << "xxx: Copy assignment operator...\n"; //add a statement for when the copy assignment operator is called
        return *this;
    }

	template<typename T>
    vector<T>::~vector(){
        delete[] the_data;
		std::cout << "xxx: Destructor...\n"; //add a statement for when the destructor is called
    }

    /** *********************** OTHER MEMBERS *********************** **/
	template<typename T>
    bool vector<T>::empty() const {
        return the_size == 0;
    }

	template<typename T>
    size_t vector<T>::size() const {
        return the_size;
    }

	template<typename T>
    size_t vector<T>::capacity() const {
        return the_capacity;
    } 

	template<typename T>
    T vector<T>::front() const {
        return *the_data;
    }

	template<typename T>
    T vector<T>::back() const {
        return *(the_data + the_size - 1);
    } 

	template<typename T>
    T vector<T>::at( size_t index ) const {
        if ( index < the_size )
            return the_data[index];
        return the_data[0];
    }

	template<typename T>
    T& vector<T>::operator[]( size_t index ){
        return the_data[index];
    }
	template<typename T>
    T vector<T>::operator[]( size_t index ) const {
        return the_data[index];
    }

	/**
	Generic += takes a vector and modifies this vector so that its ith element
	is summed with the ith element of the input vector
	*/
	template<typename T>
	vector<T>& vector<T>::operator+=(const vector<T>& rhs) {
		for (size_t i = 0; i < the_size; ++i) { //iterate over the vectors
			the_data[i] += rhs[i]; //add the element from the right vector to the element from this vector
		}
		return *this; //return a reference to this vector
	}

	/**
	Generic * which takes an object of type T and multiplies each value
	in this vector by T
	*/
	template<typename T>
	vector<T> vector<T>::operator*(const T& rhs) {
		for (size_t i = 0; i < the_size; ++i) { //iterate over the vector
			the_data[i] = the_data[i] * rhs; //multiply the element by T
								   //the right hand side of the expression is written this way in order to get the
								   //behavior we want when multiplying a string and a vector<string>
		}
		return this;
	}

	template<typename T>
    void vector<T>::dump_data_to( std::ostream& out ) const {
        out << "Vector (dump): ";
        for ( size_t i = 0 ; i < the_capacity ; ++i )
            out << the_data[i] << ' ';
        out << '\n';
    }
	template<typename T>
    void vector<T>::dump_data() const {
        dump_data_to( std::cout );
    }

	template<typename T>
    void vector<T>::push_back( T new_value ){
        if ( the_size == the_capacity ) 
            reserve( the_capacity + 1 );     // `the_data` is reassigned

        the_data[the_size++] = new_value;
    }

    // This implementation does not shrink the vector (ever)
	template<typename T>
    void vector<T>::pop_back(){
        if ( the_size > 0 )
            --the_size;
    }


	template<typename T>
    void vector<T>::reserve( size_t new_capacity ){
        if ( new_capacity > the_capacity ) {
            if ( new_capacity <= 2 * the_capacity )
                new_capacity = 2 * the_capacity;

            T* old_location = the_data;

            the_data = new T[new_capacity]; //now we are using arrays of generic T, not double
            the_capacity = new_capacity;

            for ( size_t i = 0 ; i < the_size ; ++i )
                the_data[i] = old_location[i];

            delete old_location;
        }
    }

} // end Pic10b namespace



/** ************************ OTHER FUNCTIONS ************************ **/

/**
Overloaded output function for when our vector is of type int
*/
std::ostream& operator<<(std::ostream& out, const Pic10b::vector<int>& v) {
	out << '{'; //as we are dealing with numbers, we add braces...
	for (size_t i = 0; i < v.size()-1; ++i) //iterate over all the elements in the vector
		out << v[i] << ", "; //... and commas
	out << v[v.size() - 1] << '}';
	return out;
}

/**
Overloaded output function for when our vector is of type double
*/
std::ostream& operator<<(std::ostream& out, const Pic10b::vector<double>& v) {
	out << '{'; //as we are dealing with numbers, we add braces...
	for (size_t i = 0; i < v.size() - 1; ++i) //iterate over all the elements in the vector
		out << v[i] << ", "; //... and commas
	out << v[v.size() - 1] << '}';
	return out;
}

/**
Overloaded output function for when our vector is of type string
*/
std::ostream& operator<<(std::ostream& out, const Pic10b::vector<std::string>& v) {
	out << "[ "; //now we want to use brackets as we are dealing with strings
	for (size_t i = 0; i < v.size() - 1; ++i) //iterate over all the elements in the vector
		out << v[i] << ", ";
	out << v[v.size() - 1] << " ]";
	return out;
}


/**
Generic output function for our vector, iterates over all the elements and prints them
separated with spaces
*/
template<typename T>
std::ostream& operator<<(std::ostream& out, const Pic10b::vector<T>& v) {
	for (size_t i = 0; i < v.size(); ++i) //iterate over the elements
		out << v[i] << ' '; //print the element followed by a space
	return out;
}

/**
Overloaded * for strings so that multiplying our vector with a string would behave
as specified, adding the strings together with a space inbetween
*/
std::string operator*(const std::string& lhs, std::string rhs) {
	return lhs + ' ' + rhs; //add the strings with a space between them
}

/**
Generic * which takes two vectors and outputs their dot product
*/
template<typename T>
T operator*(const Pic10b::vector<T>& lhs, const Pic10b::vector<T>& rhs) {
	int min_sz = lhs.size() < rhs.size() ? lhs.size() : rhs.size(); //get the minimum of the sizes of the vectors
	T result = T();
	for (size_t i = 0; i < min_sz; ++i) { //iterate over the values in the vectors
		result += (lhs[i] * rhs[i]); //multiply the individual values and sum them
	}
	return result;
}

/**
Generic * which takes an object of type T on the left and a vector of T on the right,
multiplies each value of the vector by T
*/
template<typename T>
Pic10b::vector<T> operator*(const T& lhs, Pic10b::vector<T> rhs) {
	for (size_t i = 0; i < rhs.size(); ++i) { //iterate over the vector
		rhs[i] = lhs * rhs[i]; //multiply the element by T
		//the right hand side of the expression is written this way in order to get the
		//behavior we want when multiplying a string and a vector<string>
	}
	return rhs;
}

/**
Generic + which takes two vectors and returns a vector whose ith element is the sum
of the ith elements of the input vectors
*/
template<typename T>
Pic10b::vector<T> operator+(Pic10b::vector<T> lhs, const Pic10b::vector<T>& rhs) {
	return lhs += rhs; //return the sum of the vectors
}

/**
Generic < comparison operator, takes two vectors and returns true if 
the magnitude of the left vector is less than the magnitude of the right vector
*/
template<typename T>
bool operator<(const Pic10b::vector<T>& lhs, const Pic10b::vector<T>& rhs) {
	return (lhs * lhs) < (rhs * rhs); //compare the magnitudes
}

/**
Generic <= comparison operator, takes two vectors and returns true if the left
vector is less than or equal to the right
*/
template<typename T>
bool operator<=(const Pic10b::vector<T>& lhs, const Pic10b::vector<T>& rhs) {
	return !(rhs < lhs); //lhs <= rhs == !(rhs < lhs)
}

/**
Generic > comparison operator, takes two vectors and returns true if the left
vector is greater than the right vector
*/
template<typename T>
bool operator>(const Pic10b::vector<T>& lhs, const Pic10b::vector<T>& rhs) {
	return rhs < lhs; //lhs > rhs == rhs < lhs
}

/**
Generic >= operator, takes two vectors and returns true if the left vector
is greater than or equal to the right vector
*/
template<typename T>
bool operator>=(const Pic10b::vector<T>& lhs, const Pic10b::vector<T>& rhs) {
	return !(lhs < rhs); //lhs >= rhs == !(lhs < rhs)
}

/**
Generic == operator, takes two vectors and returns true if they are equal
*/
template<typename T>
bool operator==(const Pic10b::vector<T>& lhs, const Pic10b::vector<T>& rhs) {
	return (!(lhs < rhs)) && (!(rhs < lhs)); //if the left is not less than the right and
											 //the right is not less than the left, then
											 //they must be equal
}

/**
Generic != operator, takes two vectors and returns true if they are not equal
*/
template<typename T>
bool operator!=(const Pic10b::vector<T>& lhs, const Pic10b::vector<T>& rhs) {
	return (lhs < rhs) || (rhs < lhs); //they are not equal if lhs < rhs or rhs < lhs
}

/**
Generic function for printing the contents of a vector, takes a vector
and prints each element
*/
template<typename T>
void print_vector( const Pic10b::vector<T>& v ){
    if ( v.empty() )
		std::cout << "Vector is empty\n";
    else
        std::cout << "Vector (contents): " << v << '\n' ;
} 