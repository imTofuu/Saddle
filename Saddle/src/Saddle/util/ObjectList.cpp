#include "ObjectList.h"

namespace Saddle {

    template<class T>
    void ObjectList<T>::remove(T& obj) {
        auto it = list.begin();
        int i = 0;

        while(it + i != list.end()) {
            if(&list[i] == &obj) {
                list.erase(it + i);
            }
            i++;
        }

        constList.remove(constList.begin() + i);
    }

    template<class T>
    void ObjectList<T>::remove(int i) {
        list.erase(list.begin() + i); constList.erase(constList.begin() + i);
    }

}