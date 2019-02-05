#include <iostream>   // std::ostream, std::cout

namespace Pic10b{

    class vector{
      private:
        double* the_data;
        size_t the_size;
        size_t the_capacity;

        static const int INIT_CAP = 10;


      public:
        // The big 4 
        vector();
        vector( const vector& );
        vector& operator=( const vector& );
        ~vector();

        // Other members [public]
        bool empty() const;
        size_t size() const;
        size_t capacity() const;
        double front() const;
        double back() const; 
        double at( size_t index ) const;
        double& operator[]( size_t index );
        double operator[]( size_t index ) const; 
        void dump_data_to( std::ostream& out ) const;
        void dump_data() const;
        void push_back( double new_value );
        void pop_back();

      private:
        //Other members [private]
        void reserve( size_t new_capacity );

    }; // end Pic10b::vector


    /** ************************* THE BIG 4 ************************* **/
    vector::vector() 
      : the_data(nullptr), the_size(0), the_capacity(INIT_CAP) {

        the_data = new double[the_capacity];
    }

    vector::vector( const vector& source )
      : the_data(nullptr), the_size(source.the_size), 
        the_capacity(source.the_capacity) {

        the_data = new double[the_capacity];

        // Deep copy of internal array
        for ( int i = 0 ; i < the_size ; ++i ){
            the_data[i] = source.the_data[i];
        }
    }

    vector& vector::operator=( const vector& rhs ) {
        if ( this != &rhs ) {     // Self-assignment?
            // Release old memory and request more 
            delete[] the_data;
            the_data = new double[rhs.the_capacity];

            // Shallow copy non-pointers
            the_size = rhs.the_size;
            the_capacity = rhs.the_capacity;

            // Deep copy internal array
            for ( int i = 0 ; i < the_size ; ++i )
                the_data[i] = rhs.the_data[i];
        }
        return *this;
    }

    vector::~vector(){
        delete[] the_data;
    }

    /** *********************** OTHER MEMBERS *********************** **/
    bool vector::empty() const {
        return the_size == 0;
    }

    size_t vector::size() const {
        return the_size;
    }

    size_t vector::capacity() const {
        return the_capacity;
    } 

    double vector::front() const {
        return *the_data;
    }

    double vector::back() const {
        return *(the_data + the_size - 1);
    } 

    double vector::at( size_t index ) const {
        if ( index < the_size )
            return the_data[index];
        return the_data[0];
    }

    double& vector::operator[]( size_t index ){
        return the_data[index];
    }
    double vector::operator[]( size_t index ) const {
        return the_data[index];
    }

    void vector::dump_data_to( std::ostream& out ) const {
        out << "Vector (dump): ";
        for ( size_t i = 0 ; i < the_capacity ; ++i )
            out << the_data[i] << ' ';
        out << '\n';
    }
    void vector::dump_data() const {
        dump_data_to( std::cout );
    }


    void vector::push_back( double new_value ){
        if ( the_size == the_capacity ) 
            reserve( the_capacity + 1 );     // `the_data` is reassigned

        the_data[the_size++] = new_value;
    }

    // This implementation does not shrink the vector (ever)
    void vector::pop_back(){
        if ( the_size > 0 )
            --the_size;
    }


    void vector::reserve( size_t new_capacity ){
        if ( new_capacity > the_capacity ) {
            if ( new_capacity <= 2 * the_capacity )
                new_capacity = 2 * the_capacity;

            double* old_location = the_data;

            the_data = new double[new_capacity];
            the_capacity = new_capacity;

            for ( size_t i = 0 ; i < the_size ; ++i )
                the_data[i] = old_location[i];

            delete old_location;
        }
    }

} // end Pic10b namespace



/** ************************ OTHER FUNCTIONS ************************ **/
std::ostream& operator<<( std::ostream& out, const Pic10b::vector& v ){
    for ( size_t i = 0 ; i < v.size() ; ++i )
        out << v[i] << ' ';
    return out;
}


void print_vector( const Pic10b::vector& v ){
    if ( v.empty() )
        std::cout << "Vector is empty\n";
    else
        std::cout << "Vector (contents): " << v << '\n' ;
} 



/** ************************* THE DRIVER ************************ **/
int main(){

    using Pic10b::vector;
    using std::cout;

    cout << "Create & display empty vector (v1)\n";
    vector v1;
    print_vector(v1);
    v1.dump_data();

    int size = 15;
    cout << "\nPopulate & display vector with " << size << " entries (v1)\n";
    for ( int i = 1 ; i <= size ; ++i )
        v1.push_back(i);
    print_vector(v1);

    cout << "\nCopy non-empty vector, pop back last entry & display (v2)\n";
    vector v2(v1);
    v2.pop_back();
    print_vector(v2);

    cout << "\nReassign vector (v1 = v2) & display\n";
    v1 = v2;
    print_vector(v1);

    cout << "\nDump contents of vectors (v1,v2)\n";
    v1.dump_data();
    v2.dump_data();

    return 0;
}

/** 
    OUTPUT:

        Create & display empty vector (v1)
        Vector is empty
        Vector (dump): 0 0 0 0 0 0 0 0 0 0 

        Populate & display vector with 15 entries (v1)
        Vector (contents): 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 

        Copy non-empty vector, pop back last entry & display (v2)
        Vector (contents): 1 2 3 4 5 6 7 8 9 10 11 12 13 14 

        Reassign vector (v1 = v2) & display
        Vector (contents): 1 2 3 4 5 6 7 8 9 10 11 12 13 14 

        Dump contents of vectors (v1,v2)
        Vector (dump): 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 0 0 0 0 0 
        Vector (dump): 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 0 0 0 0 0 

**/
