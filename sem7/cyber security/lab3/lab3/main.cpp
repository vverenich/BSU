#include <iostream>
#include <cmath>
#include <vector>
#include <random>
#include <functional>

#include <cryptopp/md5.h>
#include "cryptopp/cryptlib.h"
#include "cryptopp/sha.h"
#include <cryptopp/filters.h>

/// Точка
template <class Number>
class Point {
  using ThisT = Point;
 public:
  Point(Number x, Number y) : x(x), y(y) {}
  Point() : ThisT(static_cast<Number>(0), static_cast<Number>(0)) {}

  bool operator==(Point<Number>& point) {
      return (point.x == this->x) && (point.y == this->y);
  }

  template <class T>
  friend std::ostream& operator<<(std::ostream& stream, Point<T>& point);

  Number  x;
  Number  y;
};

template <class Number>
std::ostream& operator<<(std::ostream& stream, Point<Number>& point) {
  stream << "(" << point.x << ", " << point.y << ")";
  return stream;
}

namespace Math {
      template <class Integer>
      Integer power (Integer base, Integer exponent, Integer modulus) {
      Integer result = 1;
      base = base % modulus;

      while (exponent > 0) {
          if (exponent % 2 == 1)
              result = (result * base) % modulus;

          exponent = exponent >> 1;
          base = (base * base) % modulus;
      }

      return result;
    }

    template <class Integer>
    Integer _divide_byModulus( Integer a,  Integer b,  Integer modulus) {
      Integer lambda = ((a % modulus) + modulus) % modulus; // Вычисляем остаток от деления с положительным знаком
      Integer phi = modulus - 1; // Функция Эйлера для заданного модуля
      Integer inverseB = power(b, phi - 1, modulus);
      lambda = (lambda * inverseB) % modulus;

      return lambda;
    }

    template <class Integer>
    Integer getDivisionByModulus( Integer a,  Integer b) {

      if (a >= 0 ) {
          return a % b;
      } else {
          Integer lambda = a % b;
          if (lambda < 0)
              lambda += b;

          return lambda;
      }

    }
    }


    /// Проверка валидности параметров эллиптической группы
    template <class Integer>
    bool IsValidGroupParams(Integer a, Integer b, Integer modulus) {
      static auto const isPrime = [](Integer m){ return true; };

      if (a >= modulus || b >= modulus || !isPrime(modulus))
          return false;

      Integer r = static_cast<Integer>(4 * std::pow(a, 3) + 27 * std::pow(b, 2)) % modulus;
      return 0 != r;
    }


    /// Эллиптическая группа
    template <class Integer>
    class CurveGroup {
  public:
      CurveGroup(Integer a, Integer b, Integer modulus) : a(a), b(b), M(modulus) {
          if (!IsValidGroupParams(a, b, modulus))
              throw std::runtime_error("Invalid arguments");
      }

      Integer GetNegative(Integer v) const {
          return M - v;
      }

      std::vector<Integer> GetSqrt(Integer v) const {
          using RT = std::vector<Integer>;

          for (Integer s = 0; s < M; ++s) {
              if ((s * s) % M == v)
                  return s == 0 ? RT{0} : RT{s, GetNegative(s)};
          }
          return {};
      }

      std::vector<Point<Integer>> GetPoints() const {
          std::vector<Point<Integer>> points;

          for (Integer x = 0; x < M; ++x) {
              Integer y_pow = static_cast<Integer>(std::pow(x, 3) + a * x + b) % M;
              for (auto y : GetSqrt(y_pow))
                  points.push_back(Point<Integer>(x, y));
          }

          return points;
      }


  Point<Integer> getSum(Point<Integer>& point1, Point<Integer>& point2) {
      int32_t lambda{};

      if (point2 == point1) {
          lambda = Math::_divide_byModulus((3 * point1.x * point1.x + a), (2 * point1.y), M);
      } else {
          lambda = Math::_divide_byModulus((point2.y - point1.y), (point2.x - point1.x), M);
      }

      //std::cout << "\n\n" << lambda << "\n\n";

      Point<Integer> point{};
      point.x = Math::getDivisionByModulus((lambda * lambda - point1.x - point2.x) , M);
      point.y = Math::getDivisionByModulus((lambda * (point1.x - point.x) - point1.y), M);

      return point;
  }

  Point<Integer> getMultiplication(Point<Integer>& point, size_t number) {
      Point<Integer> result{point.x, point.y};
      for (int i{1}; i < number; ++i) {
          result = getSum(result, point);
      }

      return result;
  }



  Integer getC(Point<Integer>& point) {
      int a{1};
      int b{2};

      Point<Integer> point1 = point;
      Point<Integer> point2 = point;

      int count = 0;
      while (true) {
          ++ count;
          if (count == 10) {
                  return -1;
          }
          point2 = getMultiplication(point, b);
          for (a = 1; a < b; ++a) {
              point1 = getMultiplication(point, a);
            if (point1 == point2) {
                  std::cout << point1 << "\n";
                std::cout << "a: " << a << "\n";
                std::cout << "b: " << b << "\n";
                return b - a;
            }
          }
      }

      ++b;
  }

  Integer const a;
  Integer const b;
  Integer const M;
};

template <typename T>
T randomFrom(const T min, const T max)
{
  static std::random_device rdev;
  static std::default_random_engine re(rdev());
  typedef typename std::conditional<
      std::is_floating_point<T>::value,
      std::uniform_real_distribution<T>,
      std::uniform_int_distribution<T>>::type dist_type;
  dist_type uni(min, max);
  return static_cast<T>(uni(re));
}

int main() {
  // task 1
  std::cout << "-------- TASK 1 --------\n";
  int a = 0;
  int b = -4;
  int M = 211;
  Point<int> G{2, 2};

  // task 2
  std::cout << "-------- TASK 2 --------\n";
  CurveGroup<int> group(a, b, M);
  auto points = group.GetPoints();

  std::cout << "a: " << a << std::endl;
  std::cout << "b: " << b << std::endl;
  std::cout << "M: " << M << std::endl;
  std::cout << "Calculated " << points.size() << " points:" << std::endl;

  for (auto point : points) {
      std::cout << point << std::endl;
  }

  // task 3
  std::cout << "-------- TASK 3 --------\n";
  //int32_t nA = randomFrom<decltype(nA)>(0, M);
  int32_t nA = 121;
  std::cout << "nA < M: " << nA << "\n";
  auto pA = group.getMultiplication(G, nA);
  std::cout << "pA: " << pA <<  "\n";
  //int32_t nB = randomFrom<decltype(nB)>(0, M);
  int32_t nB = 203;
  std::cout << "nB < M: " << nB << "\n";
  auto pB = group.getMultiplication(G, nB);
  std::cout << "pB: " << pB <<  "\n";
  auto K = group.getMultiplication(pB, nA);
  std::cout << "K = nA * pB = nB * pA: " << K <<  "\n";

  // task 4
  std::cout << "-------- TASK 4 --------\n";
  std::string msg = "Yoda said, Do or do not. There is no try.";
  std::cout << "message: " << msg << "\n";

  std::cout << "User A" << "\n";
  nA = randomFrom<decltype(nA)>(1, 200);
  std::cout << "secret key nA: " << nA << "\n";
  pA = group.getMultiplication(G, nA);
  std::cout << "public key pA: " << pA << "\n";
  std::size_t hashCodeA = std::hash<std::string>{}(msg);
  std::cout << "hash code: " << hashCodeA << "\n";
  size_t q = 1000;
  int32_t k = randomFrom<decltype(k)>(1, q);
  std::cout << "k( < q - 1): " << k << "\n";
  auto kG = group.getMultiplication(G, k);
  std::cout << "kG : " << kG << "\n";
  size_t r = Math::getDivisionByModulus(static_cast<size_t>(kG.x), q);
  std::cout << "r: " << r << "\n";
  int32_t s = Math::_divide_byModulus((hashCodeA + nA * r), static_cast<size_t>(k), static_cast<size_t>(q));
  std::cout << "s : " << s << "\n";
  std::cout << "(r, s): " << "(" << r << ", " << s << ")\n";


  std::cout << "User B" << "\n";
  std::size_t hashCodeB = std::hash<std::string>{}(msg);
  std::cout << "hash code: " << hashCodeB << "\n";
  std::cout << "1 <= " << r << " <= q - 1, " << "1 <= " << s << " <= q - 1\n";
  int32_t w = Math::_divide_byModulus(static_cast<size_t>(1), static_cast<size_t>(s), q);
  std::cout << "w: " << w << "\n";
  auto u1 = Math::getDivisionByModulus(static_cast<size_t>(hashCodeB * w), q);
  auto u2 = Math::getDivisionByModulus(static_cast<size_t>(r * w), q);
  std::cout << "u1 = " << u1 << ", u2 = " << u2 << "\n";
  auto u1G = group.getMultiplication(G, u1);
  auto u2pA = group.getMultiplication(pA, u2);
  auto u1G_u2pA = group.getSum(u1G, u2pA);
  auto r_ = Math::getDivisionByModulus(static_cast<size_t>(u1G_u2pA.x), q);
  std::cout << "u1 * G + u2 * pA = " << u1G_u2pA << ", r* = " << r_ << "\n";

  /*
  auto c = group.getC(points.at(0));
  std::cout << "C: " << c << "\n";
    */

  /*
  Point<int> point2{1, 0};
  Point<int> point1{192, 201};
  auto point = group.getSum(point1, point2);
  std::cout << point << "\n";
  */





  /*
  //using namespace CryptoPP;
  CryptoPP::HexEncoder encoder(new FileSink(std::cout));

  std::string msg = "Yoda said, Do or do not. There is no try.";
  std::string digest;

  CryptoPP::SHA1 hash;
  hash.Update((const byte*)msg.data(), msg.size());
  digest.resize(hash.DigestSize());
  hash.Final((byte*)&digest[0]);

  std::cout << "Message: " << msg << std::endl;

  std::cout << "Digest: ";
  CryptoPP::StringSource(digest, true, new CryptoPP::Redirector(encoder));
  std::cout << std::endl;
  */



    /*
  Point<int> point1{16, 5};
  Point<int> point2{16, 5};
  auto point3 = group.getSum(point1, point2);
  std::cout << "\n\n" << point3.x << " " << point3.y <<"\n\n";
  */

  /*
  Point<int> point{0, 376};
  for (int i = 0; i < 386; ++i) {
      Point<int> point2{0, 376};
      point = group.getSum(point, point2);
  }
  std::cout << "\n\n" << point.x << " " << point.y <<"\n\n";
    */







  return 0;
}
