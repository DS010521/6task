#include <iostream>
#include <clocale>
#include <string>
#include <fstream>
using namespace std;

//Здравствуйте. Задача номер 6(7), использование односвязного списка
//добавление, удаление, и прочее
//написал комментарии, чтобы сымитировать ответы на вопросы

struct books {
    char a;
    int pages;
    string author;
    union { //объединение нескольких структур, разные структуры занимают в памяти один и тот же участок памяти
        struct {
            int monthNum;
        } article;
        struct {
            int year;
        } book;
    }bookType;
};

typedef struct linkedListNode {
    books* str;
    struct linkedListNode* next;
} listNode;

typedef struct linkedList {
    listNode* head;
    listNode* tail; 
} list;

//a->b = (*a).b
//"точка" и "стрелочка" позволяют получить доступ к элементам структур
//"точка" используется для обычного доступа к элементам структур,
//"стрелочка" используется для доступа к элементам структуры с помощью указателей
//конструкция a->b означает, что значение, содержащееся в b возвращется в структуру a

list* init(void) {
    list* node = (list*)malloc(sizeof(list)); //выделяю память для узла
    node->head = NULL;
    node->tail = node->head; 
    return node;
}

void addElement(books* a, list* root) {
    listNode* node = (listNode*)malloc(sizeof(listNode)); //память под узел списка
    node->str = a;
    node->next = root->head; //указатель на голову, т.к. добавляем в начало
    root->head = node;
}

//инициализация первых элементов списка, чтобы не вводить руками и было сразу что удалить
void initBooks(list* list) {
    books* a = new books;
    a->a = 'A';
    a->author = "Abraam";
    a->pages = 24;
    a->bookType.article.monthNum = 2;
    addElement(a, list);
    a = new books;
    a->a = 'A';
    a->author = "Borker";
    a->pages = 12;
    a->bookType.article.monthNum = 5;
    addElement(a, list);
    a = new books;
    a->a = 'B';
    a->author = "Connel";
    a->pages = 278;
    a->bookType.book.year = 1997;
    addElement(a, list);
    a = new books;
    a->a = 'B';
    a->author = "Doren";
    a->pages = 350;
    a->bookType.book.year = 2003;
    addElement(a, list);
}

//вывожу список всех книг
void showAllBooks(list* list) {
    listNode* node = list->head;
    while (node != NULL) {
        cout << "Number of pages: " << node->str->pages << ";" << endl;
        cout << "Author: " << node->str->author << ";" << endl;
        if (node->str->a == 'A') {
            cout << "Type of book: article" << endl;
            cout << "Month of publication: " << node->str->bookType.article.monthNum << ";" << endl;
            cout << "______________" << endl;
        }
        if (node->str->a == 'B') {
            cout << "Type of book:novel" << endl;
            cout << "Year of publication: " << node->str->bookType.book.year << ";" << endl;
            cout << "______________" << endl;
        }
        node = node->next;
    }
}

//функция, отвечающая за удаление элемента из списка
void deleteBook(int j, list* list) {
    listNode* node = list->head, * temp = NULL, * temp1 = NULL; //первый узел - голова, остальные дополнительные
    int i = 1;
    if (node == NULL) {
        return;
    }
    while (node && i != j) { //нахожу j-ый узел, который хочу удалить, в node сохраняю ссылку на следующий
        temp = node;
        i++;
        node = node->next;
    }
    //так как добавляю элемент в начало листа, то фактически начало листа - последний добавленный элемент
    if (node == list->head) { //если удаляемый элемент - начало листа
        temp1 = list->head->next;
        free(list->head);
        list->head = temp1;
        return;
    }
    if (!node) { //если не существует такого узла
        return;
    }
    temp->next = node->next;
    free(node);
}

//функция, отвечающая за добавление элемента в список
//автор и количество страниц в книге вводится вне зависимости, A или B введено
//если введено A - спрашивает месяц публикации статьи, если B - год публикации книги-романа

void addBook(list* list) {
    books* bk = new books;
    cout << "Enter the book type (A - article, B - novel): ";
    cout << endl;
    cin >> bk->a;
    if (bk->a == 'A') {
        cout << "Type month of publication: ";
        cin >> bk->bookType.article.monthNum;
        cout << endl;
    }
    else if (bk->a == 'B') {
        cout << "Type year of publication: ";
        cin >> bk->bookType.book.year;
        cout << endl;
    }
    cout << "Type the author: ";
    cin >> bk->author;
    cout << endl;
    cout << "Type number of pages: ";
    cin >> bk->pages;
    cout << endl;
    addElement(bk, list);
}

void showMenu() {
    cout << "0) Exit" << endl;
    cout << "1) Show all" << endl;
    cout << "2) Delete element" << endl;
    cout << "3) Add new element;" << endl;
}

int main()
{
    list* list = init();
    initBooks(list);
    int a = 9;
    while (a != 0) {
        showMenu();
        cin >> a;
        switch (a) {
        case 0: break;
        case 1: showAllBooks(list);
            break;
        case 2: cout << "Index of element: ";
            int j;
            cin >> j;
            deleteBook(j, list);
            break;
        case 3: addBook(list);
            break;
        default: break;
        }
    }
}