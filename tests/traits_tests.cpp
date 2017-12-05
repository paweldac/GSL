///////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2015 Microsoft Corporation. All rights reserved.
//
// This code is licensed under the MIT License (MIT).
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
///////////////////////////////////////////////////////////////////////////////

#include <catch/catch.hpp>
#include <gsl/traits>
#include <memory>

TEST_CASE("unique_ptr should provide element_type* get()")
{
    REQUIRE(gsl::traits::has_get_member<std::unique_ptr<int>>::value == std::true_type{});
}

TEST_CASE("shared_ptr should provide element_type* get()")
{
    REQUIRE(gsl::traits::has_get_member<std::unique_ptr<int>>::value == std::true_type{});
}

TEST_CASE("raw int ptr has no get() member")
{
    REQUIRE(gsl::traits::has_get_member<int*>::value == std::false_type{});
}

template <typename T>
struct WrongTestSmartPtr
{
    WrongTestSmartPtr(T* p) : p_(p) {}
    void get() const { return p_; }
    T* p_ = nullptr;
};

TEST_CASE("custom smart pointer providing void get()")
{
    REQUIRE(gsl::traits::has_get_member<WrongTestSmartPtr<int>>::value == std::false_type{});
}

template <typename T>
struct ProperTestSmartPtr
{
    ProperTestSmartPtr(T* p) : p_(p) {}
    T* get() const { return p_; }
    T* p_ = nullptr;
};

TEST_CASE("custom smart pointer providing element_type* get()")
{
    REQUIRE(gsl::traits::has_get_member<ProperTestSmartPtr<int>>::value == std::true_type{});
}
