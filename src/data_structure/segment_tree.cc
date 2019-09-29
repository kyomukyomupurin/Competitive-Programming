/**
 *  Segment Tree
**/

#include <functional>
#include <vector>

// verified by
// https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/all/DSL_2_A
class SegmentTree {
 public:
  SegmentTree(const std::vector<int>& vec, const int& initial_value,
              std::function<int(int, int)> operation)
      : initial_value_(initial_value), vec_(vec), operation_(operation) {
    Initialize();
  }
  void Update(int position, int new_value);
  int Query(int a, int b, int k, int l, int r);

 private:
  int n_;
  const int initial_value_;
  const std::vector<int> vec_;
  std::vector<int> data_;
  std::function<int(int, int)> operation_;
  void Initialize();
};

void SegmentTree::Initialize() {
  int vsize = static_cast<int>(vec_.size());
  n_ = 1;
  while (n_ < vsize) {
    n_ <<= 1;
  }
  data_.assign(2 * n_ - 1, initial_value_);
  for (int i = 0; i < vsize; ++i) {
    data_[i + n_ - 1] = vec_[i];
  }
  for (int i = n_ - 2; i >= 0; --i) {
    data_[i] = operation_(data_[2 * i + 1], data_[2 * i + 2]);
  }
}

void SegmentTree::Update(int position, int new_value) {
  position += n_ - 1;
  data_[position] = new_value;
  while (position > 0) {
    position = (position - 1) / 2;
    data_[position] =
        operation_(data_[2 * position + 1], data_[2 * position + 2]);
  }
}

// return Query[a, b)
int SegmentTree::Query(int a, int b, int k = 0, int l = 0, int r = -1) {
  if (r < 0) r = n_;
  if (r <= a || b <= l) return initial_value_;
  if (a <= l && r <= b) return data_[k];
  int vl = Query(a, b, 2 * k + 1, l, (l + r) / 2);
  int vr = Query(a, b, 2 * k + 2, (l + r) / 2, r);
  return operation_(vl, vr);
}

// non-recursive version
// verified by
// https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/all/DSL_2_A
template <typename T>
class SegmentTree {
 public:
  SegmentTree(const std::vector<T>& vec, const T& initial_value,
              std::function<T(T, T)> operation)
      : initial_value_(initial_value), vec_(vec), operation_(operation) {
    Initialize();
  }
  void Update(int position, T new_value) {
    position += n_;
    data_[position] = new_value;
    while (position > 0) {
      position >>= 1;
      data_[position] =
          operation_(data_[2 * position], data_[2 * position + 1]);
    }
  }
  // return Query[a, b)
  T Query(int a, int b) {
    T vl = initial_value_, vr = initial_value_;
    for (a += n_, b += n_; a < b; a >>= 1, b >>= 1) {
      if (a & 1) vl = operation_(vl, data_[a++]);
      if (b & 1) vr = operation_(data_[--b], vr);
    }
    return operation_(vl, vr);
  }

 private:
  int n_;
  const T initial_value_;
  const std::vector<T> vec_;
  std::vector<T> data_;
  std::function<T(T, T)> operation_;
  void Initialize() {
    int vsize = static_cast<int>(vec_.size());
    n_ = 1;
    while (n_ < vsize) {
      n_ <<= 1;
    }
    data_.assign(2 * n_, initial_value_);
    for (int i = 0; i < vsize; ++i) {
      data_[i + n_] = vec_[i];
    }
    for (int i = n_ - 1; i > 0; --i) {
      data_[i] = operation_(data_[2 * i], data_[2 * i + 1]);
    }
  }
};