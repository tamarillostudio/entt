#ifndef ENTT_CORE_FAMILY_HPP
#define ENTT_CORE_FAMILY_HPP


#include "../config/config.h"
#include "fwd.hpp"


namespace entt {


/**
 * @brief Dynamic identifier generator.
 *
 * Utility class template that can be used to assign unique identifiers to types
 * at runtime. Use different specializations to create unique sets of values.
 */
template<typename...>
class family {
    [[nodiscard]] static id_type next() ENTT_NOEXCEPT {
        static ENTT_MAYBE_ATOMIC(id_type) value{};
        return value++;
    }

public:
    /*! @brief Unsigned integer type. */
    using family_type = id_type;

    /**
     * @brief Assigns an unique identifier to the given type.
     * @tparam Type Type for which to generate an identifier.
     * @return Statically generated unique identifier for the given type.
     */
    template<typename Type>
    [[nodiscard]] static family_type type() ENTT_NOEXCEPT {
        static const family_type value = next();
        return value;
    }
};


}


#endif
