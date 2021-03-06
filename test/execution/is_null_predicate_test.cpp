#include "execution/sql/functions/is_null_predicate.h"
#include <ctime>
#include "execution/sql/value.h"
#include "execution/tpl_test.h"

namespace terrier::execution::sql::test {

class IsNullPredicateTests : public TplTest {};

// NOLINTNEXTLINE
TEST_F(IsNullPredicateTests, IsNull) {
#define CHECK_IS_NULL_FOR_TYPE(TYPE)                                \
  {                                                                 \
    auto result = BoolVal::Null();                                  \
    const auto val = TYPE::Null();                                  \
    terrier::execution::sql::IsNullPredicate::IsNull(&result, val); \
    EXPECT_FALSE(result.is_null_);                                  \
    EXPECT_TRUE(result.val_);                                       \
  }

  CHECK_IS_NULL_FOR_TYPE(BoolVal);
  CHECK_IS_NULL_FOR_TYPE(Integer);
  CHECK_IS_NULL_FOR_TYPE(Real);
  CHECK_IS_NULL_FOR_TYPE(StringVal);
  CHECK_IS_NULL_FOR_TYPE(DateVal);
  CHECK_IS_NULL_FOR_TYPE(TimestampVal);

#undef CHECK_IS_NULL_FOR_TYPE
}

// NOLINTNEXTLINE
TEST_F(IsNullPredicateTests, IsNotNull) {
#define CHECK_IS_NOT_NULL_FOR_TYPE(TYPE, INIT)                      \
  {                                                                 \
    auto result = BoolVal::Null();                                  \
    const auto val = TYPE(INIT);                                    \
    terrier::execution::sql::IsNullPredicate::IsNull(&result, val); \
    EXPECT_FALSE(result.is_null_);                                  \
    EXPECT_FALSE(result.val_);                                      \
  }

  CHECK_IS_NOT_NULL_FOR_TYPE(BoolVal, false);
  CHECK_IS_NOT_NULL_FOR_TYPE(Integer, 44);
  CHECK_IS_NOT_NULL_FOR_TYPE(Real, 44.0);
  CHECK_IS_NOT_NULL_FOR_TYPE(StringVal, "44");
  CHECK_IS_NOT_NULL_FOR_TYPE(DateVal, 44);
  CHECK_IS_NOT_NULL_FOR_TYPE(TimestampVal, 44);

#undef CHECK_IS_NOT_NULL_FOR_TYPE
}

}  // namespace terrier::execution::sql::test
