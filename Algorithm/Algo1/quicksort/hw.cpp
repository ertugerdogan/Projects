#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <chrono>

using namespace std;

int swap_count = 0;
int partition_count = 0;

struct book
{
    int bookID;
    string title;
    string authors;
    float average_rating;
    string isbn;
    string isbn13;
    string language_code;
    string num_pages;
    string ratings_count;
    string text_reviews_count;
    string publication_date;
    string publisher;
}; 

vector<book> readcsv(string file_name)
{
    vector<book> result;

    ifstream myFile(file_name);
    string line, colname;
    
    getline(myFile, line);
    
    while(getline(myFile, line)){
        
        book a_book;

        int num;

        num = line.find(",");
        a_book.bookID = stoi(line.substr(0,num));
        line.erase(0,num+1);
        
        num = line.find(",");
        a_book.title = line.substr(0,num);
        line.erase(0,num+1);
        
        num = line.find(",");
        a_book.authors = line.substr(0,num);
        line.erase(0,num+1);

        num = line.find(",");
        a_book.average_rating = stof(line.substr(0,num));
        line.erase(0,num+1);

        num = line.find(",");
        a_book.isbn = line.substr(0,num);
        line.erase(0,num+1);
        
        num = line.find(",");
        a_book.isbn13 = line.substr(0,num);
        line.erase(0,num+1);

        num = line.find(",");
        a_book.language_code = line.substr(0,num);
        line.erase(0,num+1);
        
        num = line.find(",");
        a_book.num_pages = line.substr(0,num);
        line.erase(0,num+1);

        num = line.find(",");
        a_book.ratings_count = line.substr(0,num);
        line.erase(0,num+1);

        num = line.find(",");
        a_book.text_reviews_count = line.substr(0,num);
        line.erase(0,num+1);

        num = line.find(",");
        a_book.publication_date = line.substr(0,num);
        line.erase(0,num+1);
        
        num = line.find(",");
        a_book.publisher = line.substr(0,num);

        result.push_back(a_book);
    }
    myFile.close();

    return result;
}

void swapBooks(vector<book> &library, int book1_index, int book2_index)
{
    
    book temp;

    temp.authors = library[book2_index].authors;
    temp.average_rating = library[book2_index].average_rating;
    temp.bookID = library[book2_index].bookID;
    temp.isbn13 = library[book2_index].isbn13;
    temp.isbn = library[book2_index].isbn;
    temp.language_code = library[book2_index].language_code;
    temp.num_pages = library[book2_index].num_pages;
    temp.publication_date = library[book2_index].publication_date;
    temp.publisher = library[book2_index].publisher;
    temp.ratings_count = library[book2_index].ratings_count;
    temp.text_reviews_count = library[book2_index].text_reviews_count;
    temp.title = library[book2_index].title;

    library[book2_index].authors = library[book1_index].authors;
    library[book2_index].average_rating = library[book1_index].average_rating;
    library[book2_index].bookID = library[book1_index].bookID;
    library[book2_index].isbn13 = library[book1_index].isbn13;
    library[book2_index].isbn = library[book1_index].isbn;
    library[book2_index].language_code = library[book1_index].language_code;
    library[book2_index].num_pages = library[book1_index].num_pages;
    library[book2_index].publication_date = library[book1_index].publication_date;
    library[book2_index].publisher = library[book1_index].publisher;
    library[book2_index].ratings_count = library[book1_index].ratings_count;
    library[book2_index].text_reviews_count = library[book1_index].text_reviews_count;
    library[book2_index].title = library[book1_index].title;

    library[book1_index].authors = temp.authors;
    library[book1_index].average_rating = temp.average_rating;
    library[book1_index].bookID = temp.bookID;
    library[book1_index].isbn13 = temp.isbn13;
    library[book1_index].isbn = temp.isbn;
    library[book1_index].language_code = temp.language_code;
    library[book1_index].num_pages = temp.num_pages;
    library[book1_index].publication_date = temp.publication_date;
    library[book1_index].publisher = temp.publisher;
    library[book1_index].ratings_count = temp.ratings_count;
    library[book1_index].text_reviews_count = temp.text_reviews_count;
    library[book1_index].title = temp.title;

    swap_count++;
}

int partition(vector<book> &library, int start, int end)
{
    int i = start;
    int j = start;
    
    float pivot = library[end].average_rating;

    while(j >= i){
        if(j == end){
            if(library[i].average_rating < pivot){
                i = i + 1;
            }
            swapBooks(library, i, j);
            break;
        }
        if(library[j].average_rating < pivot){
            swapBooks(library, i, j);
            i = i + 1;
        }
        j = j+1;
    }
    partition_count++;
    return i;
}
 
void quickSort(vector<book> &library, int start, int end)
{  
    if (start>=end)
        return;

    int p = partition(library, start, end);
 
    quickSort(library, start, p-1);
    quickSort(library, p+1, end);
}

void writecsv(string file_name, vector<book> books)
{
    ofstream output_csv(file_name);
    int i;
    for(i=0;i<books.size();i++){
        output_csv<<books[i].bookID<<", "<<books[i].average_rating<<endl;
    }
    output_csv.close();
}

void print_array(vector<book> library){
    for(int i=0; i<library.size(); i++){
        cout << library[i].bookID << ", " << library[i].average_rating << endl;
    }
}
int main()
{
    vector<book> books=readcsv("books.csv");
    
    cout << endl << "Unsorted Array: " << endl;
    print_array(books);

    auto begin = std::chrono::high_resolution_clock::now();

    quickSort(books, 0, books.size()-1);
    
    auto end = std::chrono::high_resolution_clock::now();
    auto nanosecond =  std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count();

    cout << endl << "Sorted Array: " << endl;
    print_array(books);


    cout<<endl<<"Working Quarter Sized Array: "<<endl;
    cout<<"Execution Time(Nanoseconds): "<<nanosecond<<endl;
    cout<<"Number Of Swaps: " <<swap_count<<endl;
    cout<<"Number Of Partition Calls: "<<partition_count<<endl;
    
    writecsv("books.csv", books);

    return 0;
}