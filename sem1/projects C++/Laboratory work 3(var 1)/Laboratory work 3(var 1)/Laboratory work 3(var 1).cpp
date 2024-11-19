 #include <iostream>
 #include<random>
 #include<ctime>

int main()
{
    int N = 0;
    while (N < 1){
        std::cout << "Enter a number of array elements(at least 1 element): ";
        std::cin >> N;
        if (N < 1){
            std::cout << "You made an illegal choice.";
        }
    }

    int choice = 0;
    int* array = new int[N];
    std::cout << "\nDo you want to enter all the elements(enter 1) or to generate them(enter 2) : ";
    
    while (choice != 2 && choice != 1){
        std::cin >> choice;
        if (choice != 2 && choice != 1){
            std::cout << "You made an illegal choice.";
            std::cout << "Enter 1 or 2: ";
        }
    }

    if (choice == 1){
        for (int i = 0; i < N; ++i){
            std::cout << "Enter element number " << i+1 << " :";
            std::cin >> array[i];
        }
    }

    else{
        std::default_random_engine generator(time(0));
        std::uniform_int_distribution<int> distribution(-100, 100);
        std::cout << "\nYour array: ";
        for (int i = 0; i < N; ++i){
            array[i] =distribution(generator);
            std::cout << "\n"<<array[i];
        }

    }
    
    int p = 1;
    for (int i = 1; i < N; i += 2){
        p *= array[i];
    }
    std::cout << "\n1)Product of even elements: " << p;
    int n1 = -2;
    int n2 = -2;
    for (int i = 0; i < N; ++i){
        if (array[i] == 0 && n1 == -2){
            n1 = i;
        }

        else if (array[i]==0){
            n2 = i;
        }
    }

    int sum = 0;
    if (n2 == (n1 + 1)){
        std::cout << "\n2)There is no elements between the first null and the last null.";
    }

    else if (n2 == -2 && n1 != -2){
        std::cout << "\n2)There is only one null among these elements.";
    }

    else if (n2 == -2 && n1 == -2){
        std::cout << "\n2)There is no null among these elements.";
    }
    else{
        for (int i = n1 + 1; i< n2; ++i){
            sum += array[i];
        }
        std::cout << "\n2)Sum of elements between the first null and the last null: " << sum;
    }

    for (int i = 0; i < N; ++i){
        if (array[i] <= 0){
            int last = i;
            for (int j = i+1; j < N; ++j){
                if (array[j ] > 0){
                    int t = array[j];
                    array[j ] = array[last];
                    array[last] = t;
                    last = j ;
                }
            }
        }
    }

    std::cout << "\n3)New array: ";
    for (int i = 0; i < N; ++i){
        std::cout <<"\n"<<array[i];
    }
     
    return 0;
}

 