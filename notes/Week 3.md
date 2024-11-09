# 1. Initialization
## 1.1. Direct Initialization
    e.g. int a(5); int b = 5
## 1.2. Uniform Initialization: **curly braces**
    e.g. float a{42.0}; 
    int b{5.0}; this will cause a compile error
** Advantage **
- No type conversion
- No precision loss
- Works for all types
- e.g. **for map:**
-  ```cpp
    std::map<std::string, int> ages{
        {"Alice", 25},
        {"Bob", 30},
        {"Charlie", 35}
    };
    // Accessing map elements
    std::cout << "Alice's age: " << ages["Alice"] << std::endl;
    std::cout << "Bob's age: " << ages.at("Bob") << std::endl;
    ```
**remarks: [] 与 at() 的区别：**

    - 使用 ages["Alice"] 会在键不存在时创建新元素并赋默认值（例如 int 类型的值为 0）。
    - 使用 ages.at("Bob") 更加安全，因为键不存在时会抛出 std::out_of_range 异常，不会插入新元素。
- e.g. **for vector:**
``` cpp
    int main() {
        // Uniform initialization of a vector
        std::vector<int> numbers{1, 2, 3, 4, 5};
        // Accessing vector elements
        for (int num : numbers) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
        return 0;
    }
```

**remarks: new way to iterate**
- 使用范围for循环遍历 vector 容器，可以方便地访问容器中的每个元素。
- 范围for循环的语法是：for (element_type element : container) {
                            // 处理元素的代码
                        }
- **SAFE!!**

## 1.3. Structured Binding: 
- A useful way to initialize some variables from data
- Ability to access multiple values returned by a function, e.g.
```cpp
std::tuple<std::string, std::string, std::string> getClassInfo() {
    std::string className = "CS106L";
    std::string buildingName = "Thornton 110";
    std::string language = "C++";
    return {className, buildingName, language};
}
int main() {
    auto [className, buildingName, language] = getClassInfo();
    std::cout << "Come to " << buildingName << " and join us for " << className
        << " to learn " << language << "!" << std::endl;
    return 0;
}
```
**Remarks:**
- auto [className, buildingName, language] = getClassInfo();
- This line declares three variables: className, buildingName, and language.
- It uses structured binding to directly assign values from the tuple returned by getClassInfo().

**Advantages:**
| 特性 | 传统写法 (std::get<index>()) | 结构化绑定（C++17）|
|------|----------------------------|-------------------|
| 简洁性 | 冗长，需要为每个元素写 std::get<index>() | 简洁，直接绑定变量 |
| 可读性 | 低，可读性差，需要根据索引了解含义 | 高，可直观理解每个变量的含义 |
| 维护性 | 容易出错，尤其当 tuple 结构变更时 | 更安全，匹配 tuple 大小时编译检查 |
| 支持版本 | C++11 及更早版本 | C++17 及更高版本 |

**Notice**
- Can use on objects where the size is known at compile-time
- where you cannot use: 
    - std::vector; 
    - std::deque; 
    - 动态分配的数组 new[]; 
    - std::tuple; 
    - 智能指针：
        - std::shared_ptr & std::unique_ptr;

- where you can use: 
    - std::array; 
    - std::pair; 
    - std::map; 
    - std::unordered_map; 
    - std::set; 
    - std::unordered_set;

# 2. References: “Declares a name variable as a reference”
tldr: a reference is an alias to an already-existing thing
## 2.1. How? Use & in the declaration
e.g. 
```cpp
        int num = 5;
        int& ref = num;
        ref = 10; // Assigning a new value through the reference
        std::cout << num << std::endl; // Output: 10
```
**Remarks:**
        ref is a variable of type int&, that is an alias to num, so when we assign 10 to ref, we also change the value of
        num, since ref is an alias for num

## 2.2. Pass by reference
reference impies that the function can modify the original argument; princplely speaking, it refers to the memory address.
        “Hey take in theactual piece of memory, don’t make a copy!”
        e.g. 
```cpp
            void swap(int& a, int& b) {
                int temp = a;
                a = b;
                b = temp;
            }
```
On the contrariy: pass by value
        Hey make a copy, don’t take in the actual variable!”


**Notice!!!**
A typical bug:
```cpp
        #include <iostream>
        #include <math.h>
        #include <vector>
            void shift(std::vector<std::pair<int, int>> &nums) {
            for (auto [num1, num2] : nums) {
                num1++;
                num2++;
            }
        }
```
**Remarks:**
            There are two functions in which the variables are expected to be modified:
                - void shift()
                - for(auto [num1, num2] : nums)
            The first one is passed by reference, so it can modify the original vector.
            The second one is passed by value, so it only modifies the copy of the vector, not the original one.

**Solution:**
```cpp
            void shift(std::vector<std::pair<int, int>> &nums) {
                for (auto &[num1, num2] : nums) {
                    num1++;
                    num2++;
                }
            }
 ``` 
A ampersand after auto solves the problem.

# 3. L-values & R-values
- An l-value can be to the left or the right of an equal sign!
        e.g. 
            x can be an l-value for instance
            because you can have something like:
            int y = x
- An r-value can only be to the right of an equal sign!
        e.g. 
            5 can be an r-value for instance
            because you can have something like:
            int y = 5
            but you cannot have something like:
            5 = x
** Remakrs **
        Remember what we said about r-values are temporary. Notice that num is being passed in by reference!
- We cannot pass in an r-value by reference because they’re temporary!
            e.g.
```cpp
                int squareN(int& num) {
                    return std::pow(num, 2);
                }
                int main()
                {
                    int lValue = 2;
                    auto four = squareN(lValue);
                    auto fourAgain = squareN(2);
                    std::cout << four << std::endl;
                    return 0;
            }
```
  The second call to squareN() passes an r-value (2) by reference, which is not allowed because r-values are temporary and cannot be referenced.


# 4. Const: A qualifier for objects that declares they cannot be modified 
## 4.1. You can’t declare a non-const reference to a const variable: it causes a compile error
e.g.
```cpp
        std::vector<int> vec{ 1, 2, 3 }; /// a normal vector

        const std::vector<int> const_vec{ 1, 2, 3 }; /// a const vector

        std::vector<int>& ref_vec{ vec }; /// a reference to 'vec'

        const std::vector<int>& const_ref{ vec }; /// a const reference

        vec.push_back(3); /// this is ok!

        const_vec.push_back(3); /// no, this is const!

        ref_vec.push_back(3); /// this is ok, just a reference!

        const_ref.push_back(3); /// this is const, compiler error!
 ```
p.s. "push_back" means adding a new element to the end of the vector.

**Solution**
- Use a const *reference* 
e.g. 
```cpp
                    const std::vector<int> const_vec{ 1, 2, 3 };
                    const std::vector<int>& good_ref{ const_vec }; /// Good! 
```

# 5. Compiling C++ Programs
## 5.1. g++
        g++ -std=c++11 main.cpp -o main
        -o: output file name
        -std=c++11: specify the C++ standard version
        - main.cpp: input file name
        - main: output file name    
