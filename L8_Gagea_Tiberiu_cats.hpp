#pragma once
#include <cstdint>
#include <iostream>
#include <string>

namespace meaw {
    class HouseCat {
    private:
        std::string name;
        std::string owner_name;
        int collar_id;
        static int next_id;
    public:
        HouseCat(const std::string &name, const std::string &owner);
        HouseCat();
        std::string ask_name() const;
        int get_collar_id() const;
        static int get_next_id();
    };

    class StrayCat {
    private:
        std::string name;
        int battles_won;
    public:
        StrayCat(const std::string &name, int battles);
        StrayCat();
        std::string ask_name() const;
    };

    class Tiger {
    private:
        std::string name;
        uint16_t stripes;
    public:
        Tiger(const std::string &name, uint16_t stripes);
        Tiger();
        std::string ask_name() const;
        uint16_t get_stripes() const;
    };

    template<typename T>
    std::string get_cat_presentation(const T &cat) {
        return cat.ask_name();
    }
    template<>
    inline std::string get_cat_presentation<Tiger>(const Tiger &cat) {
        std::cout << "Tiger " + std::to_string(cat.get_stripes());
        return "Tiger " + std::to_string(cat.get_stripes());
    }

    template<typename T, uint32_t N>
    class CatBasket {
    private:
        T static_array[N];
        T* dynamic_array;
        uint32_t current_size;
        uint32_t current_capacity;
    public:
        CatBasket();
        ~CatBasket();
        void push_back(const T &value);
        void pop_back();
        uint32_t size() const;
        uint32_t capacity() const;
        bool is_dynamic() const;
        void print_names() const;
        T& operator[](uint32_t index);
    };

    template<typename T, uint32_t N>
    CatBasket<T, N>::CatBasket() {
        dynamic_array = nullptr;
        current_size = 0;
        current_capacity = N;
    }

    template<typename T, uint32_t N>
    CatBasket<T, N>::~CatBasket() {
        if (dynamic_array != nullptr) {
            delete[] dynamic_array;
        }
    }

    template<typename T, uint32_t N>
    void CatBasket<T, N>::push_back(const T &value) {
        if (current_size < N) {
            static_array[current_size] = value;
            current_size++;
            return;
        }

        if (current_size == N && dynamic_array == nullptr) {
            current_capacity = 2 * N;
            dynamic_array = new T[current_capacity];
            for (uint32_t i = 0; i < N; i++) {
                dynamic_array[i] = static_array[i];
            }
            dynamic_array[current_size] = value;
            current_size++;
            return;
        }

        if (current_size >= N && current_size < current_capacity) {
            dynamic_array[current_size] = value;
            current_size++;
            return;
        }

        if (current_size == current_capacity) {
            current_capacity += N;
            T* temp_array = new T[current_capacity];
            for (uint32_t i = 0; i < current_size; i++) {
                temp_array[i] = dynamic_array[i];
            }
            delete[] dynamic_array;
            dynamic_array = temp_array;
            dynamic_array[current_size] = value;
            current_size++;
            return;
        }
    }

    template<typename T, uint32_t N>
    void CatBasket<T, N>::pop_back() {
        if (current_size == 0) {
            throw std::out_of_range("Der Container ist leer.");
        }
        current_size--;
    }

    template<typename T, uint32_t N>
    T &CatBasket<T, N>::operator[](uint32_t index) {
        if (index >= current_size) {
            throw std::out_of_range("Index out of range.");
        }
        if (dynamic_array != nullptr) {
            return dynamic_array[index];
        }
        return static_array[index];
    }

    template<typename T, uint32_t N>
    uint32_t CatBasket<T, N>::size() const {
        return current_size;
    }

    template<typename T, uint32_t N>
    uint32_t CatBasket<T, N>::capacity() const {
        return current_capacity;
    }

    template<typename T, uint32_t N>
    void CatBasket<T, N>::print_names() const {
        for (uint32_t i = 0; i < current_size; i++) {
            try {
                if (dynamic_array != nullptr) {
                    std::cout << dynamic_array[i].ask_name() << "\n";
                }else {
                    std::cout << static_array[i].ask_name() << "\n";
                }
            }
            catch (const std::exception &e) {
                std::cout << e.what() << "\n";
            }
        }
    }

    template<typename T, uint32_t N>
    bool CatBasket<T, N>::is_dynamic() const {
        if (dynamic_array != nullptr) {
            return true;
        }
        return false;
    }



    template<typename T>
    class CatBasket<T, 0> {
    private:
        T* dynamic_array;
        uint32_t current_size;
        uint32_t current_capacity;
    public:
        CatBasket();
        ~CatBasket();
        void push_back(const T &value);
        void pop_back();
        T& operator[](uint32_t index);
        uint32_t size() const {return current_size;}
        uint32_t capacity() const {return current_capacity;}
        bool is_dynamic() const {return true;}
        void print_names() const;
    };

    template<typename T>
    CatBasket<T, 0>::CatBasket() {
        dynamic_array = nullptr;
        current_size = 0;
        current_capacity = 0;
    }

    template<typename T>
    CatBasket<T, 0>::~CatBasket() {
        if (dynamic_array != nullptr) {
            delete[] dynamic_array;
        }
    }

    template<typename T>
    void CatBasket<T, 0>::push_back(const T &value) {
        if (current_size == current_capacity) {
            uint32_t new_capacity;
            if (current_capacity == 0) {
                new_capacity = 1;
            }else {
                new_capacity = current_capacity * 2;
            }

            T* temp_array = new T[new_capacity];
            for (uint32_t i = 0; i < current_size; i++) {
                temp_array[i] = dynamic_array[i];
            }
            delete[] dynamic_array;
            dynamic_array = temp_array;
            current_capacity = new_capacity;
        }
        dynamic_array[current_size] = value;
        current_size++;
    }

    template<typename T>
    T &CatBasket<T, 0>::operator[](uint32_t index) {
        if (index >= current_size) {
            throw std::out_of_range("Index invalid!");
        }
        return dynamic_array[index];
    }

    template<typename T>
    void CatBasket<T, 0>::pop_back() {
        if (current_size == 0) {
            throw std::out_of_range("Cosul este deja gol!");
        }
        current_size--;
    }

    template<typename T>
    void CatBasket<T, 0>::print_names() const {
        for (uint32_t i = 0; i < current_size; i++) {
            try {
                std::cout << dynamic_array[i].ask_name() << "\n";
            }
            catch (const std::exception &e) {
                std::cout << e.what() << "\n";
            }
        }
    }
}
