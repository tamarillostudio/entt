#include <functional>
#include <type_traits>
#include <gtest/gtest.h>
#include <entt/entity/entity.hpp>
#include <entt/entity/registry.hpp>

TEST(Entity, Null) {
    using traits_type = entt::entt_traits<entt::entity>;

    ASSERT_FALSE(entt::entity{} == entt::null);
    ASSERT_TRUE(entt::entity{traits_type::entity_mask} == entt::null);
    ASSERT_TRUE(entt::entity{~typename traits_type::entity_type{}} == entt::null);

    ASSERT_TRUE(entt::null == entt::null);
    ASSERT_FALSE(entt::null != entt::null);

    entt::registry registry{};
    auto entity = registry.create();

    registry.emplace<int>(entity, 42);

    ASSERT_FALSE(entity == entt::null);
    ASSERT_FALSE(entt::null == entity);

    ASSERT_TRUE(entity != entt::null);
    ASSERT_TRUE(entt::null != entity);

    ASSERT_FALSE(registry.valid(entt::null));
    ASSERT_DEATH((entity = registry.create(entt::null)), "");
}

TEST(Entity, Tombstone) {
    using traits_type = entt::entt_traits<entt::entity>;

    ASSERT_FALSE(entt::entity{} == entt::tombstone);
    ASSERT_TRUE(entt::entity{traits_type::version_mask << traits_type::entity_shift} == entt::tombstone);
    ASSERT_TRUE(entt::entity{~typename traits_type::entity_type{}} == entt::tombstone);

    ASSERT_TRUE(entt::tombstone == entt::tombstone);
    ASSERT_FALSE(entt::tombstone != entt::tombstone);

    entt::registry registry{};
    auto entity = registry.create();

    registry.emplace<int>(entity, 42);

    ASSERT_FALSE(entity == entt::tombstone);
    ASSERT_FALSE(entt::tombstone == entity);

    ASSERT_TRUE(entity != entt::tombstone);
    ASSERT_TRUE(entt::tombstone != entity);

    registry.destroy(entity, typename traits_type::version_type{traits_type::version_mask - 1u});
    registry.destroy(registry.create());

    ASSERT_DEATH((registry.destroy(entity, traits_type::version_mask)), "");
    ASSERT_DEATH((entity = registry.create(entt::tombstone)), "");
}
