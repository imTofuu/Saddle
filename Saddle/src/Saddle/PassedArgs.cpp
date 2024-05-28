#include "PassedArgs.h"

#include "Logging/Logger.h"

namespace Saddle {

    void* PassedArgs::operator[](int i) {
        SDL_CORE_ASSERT(i > m_args.size(), "Index is out of bounds for layer args access");
        if(i == m_args.size()) m_args.push_back(0);
        return m_args[i];
    }

}