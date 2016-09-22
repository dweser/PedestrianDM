#ifndef basic_ptree_hpp
#define basic_ptree_hpp

template<typename Key, typename Data, typename KeyCompare> 
class basic_ptree {
public:
  // types
  typedef basic_ptree< Key, Data, KeyCompare > self_type;
  typedef Key                                  key_type;   
  typedef Data                                 data_type;  
  typedef KeyCompare                           key_compare;
  typedef std::pair< const Key, self_type >    value_type; 
  typedef std::size_t                          size_type;  
  typedef path_of< Key >::type                 path_type;  

  // construct/copy/destruct
  basic_ptree();
  basic_ptree(const data_type &);
  basic_ptree(const self_type &);
  basic_ptree& operator=(const self_type &);
  ~basic_ptree();

  // public member functions
  void swap(self_type &) ;
  size_type size() const;
  size_type max_size() const;
  bool empty() const;
  iterator begin() ;
  const_iterator begin() const;
  iterator end() ;
  const_iterator end() const;
  reverse_iterator rbegin() ;
  const_reverse_iterator rbegin() const;
  reverse_iterator rend() ;
  const_reverse_iterator rend() const;
  value_type & front() ;
  const value_type & front() const;
  value_type & back() ;
  const value_type & back() const;
  iterator insert(iterator, const value_type &) ;
  template<typename It> void insert(iterator, It, It) ;
  iterator erase(iterator) ;
  iterator erase(iterator, iterator) ;
  iterator push_front(const value_type &) ;
  iterator push_back(const value_type &) ;
  void pop_front() ;
  void pop_back() ;
  void reverse() ;
  template<typename Compare> void sort(Compare) ;
  void sort() ;
  bool operator==(const self_type &) const;
  bool operator!=(const self_type &) const;
  assoc_iterator ordered_begin() ;
  const_assoc_iterator ordered_begin() const;
  assoc_iterator not_found() ;
  const_assoc_iterator not_found() const;
  assoc_iterator find(const key_type &) ;
  const_assoc_iterator find(const key_type &) const;
  std::pair< assoc_iterator, assoc_iterator > equal_range(const key_type &) ;
  std::pair< const_assoc_iterator, const_assoc_iterator > 
  equal_range(const key_type &) const;
  size_type count(const key_type &) const;
  size_type erase(const key_type &) ;
  iterator to_iterator(assoc_iterator) ;
  const_iterator to_iterator(const_assoc_iterator) const;
  data_type & data() ;
  const data_type & data() const;
  void clear() ;
  self_type & get_child(const path_type &) ;
  const self_type & get_child(const path_type &) const;
  self_type & get_child(const path_type &, self_type &) ;
  const self_type & get_child(const path_type &, const self_type &) const;
  optional< self_type & > get_child_optional(const path_type &) ;
  optional< const self_type & > get_child_optional(const path_type &) const;
  self_type & put_child(const path_type &, const self_type &) ;
  self_type & add_child(const path_type &, const self_type &) ;
  template<typename Type, typename Translator> 
    unspecified get_value(Translator) const;
  template<typename Type> Type get_value() const;
  template<typename Type, typename Translator> 
    Type get_value(const Type &, Translator) const;
  template<typename Ch, typename Translator> 
    unspecified get_value(const Ch *, Translator) const;
  template<typename Type> unspecified get_value(const Type &) const;
  template<typename Ch> unspecified get_value(const Ch *) const;
  template<typename Type, typename Translator> 
    optional< Type > get_value_optional(Translator) const;
  template<typename Type> optional< Type > get_value_optional() const;
  template<typename Type, typename Translator> 
    void put_value(const Type &, Translator) ;
  template<typename Type> void put_value(const Type &) ;
  template<typename Type, typename Translator> 
    unspecified get(const path_type &, Translator) const;
  template<typename Type> Type get(const path_type &) const;
  template<typename Type, typename Translator> 
    Type get(const path_type &, const Type &, Translator) const;
  template<typename Ch, typename Translator> 
    unspecified get(const path_type &, const Ch *, Translator) const;
  template<typename Type> 
    unspecified get(const path_type &, const Type &) const;
  template<typename Ch> unspecified get(const path_type &, const Ch *) const;
  template<typename Type, typename Translator> 
    optional< Type > get_optional(const path_type &, Translator) const;
  template<typename Type> 
    optional< Type > get_optional(const path_type &) const;
  template<typename Type, typename Translator> 
    self_type & put(const path_type &, const Type &, Translator) ;
  template<typename Type> self_type & put(const path_type &, const Type &) ;
  template<typename Type, typename Translator> 
    self_type & add(const path_type &, const Type &, Translator) ;
  template<typename Type> self_type & add(const path_type &, const Type &) ;

  // private member functions
  self_type * walk_path(path_type &) const;
  self_type & force_path(path_type &) ;
};

#endif /* basic_ptree_hpp */