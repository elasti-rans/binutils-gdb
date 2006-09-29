// stringpool.h -- a string pool for gold    -*- C++ -*-

#include <string>
#include <list>

// Stringpool
//   Manage a pool of unique strings.

#ifndef GOLD_STRINGPOOL_H
#define GOLD_STRINGPOOL_H

namespace gold
{

class Output_file;

class Stringpool
{
 public:
  Stringpool();

  ~Stringpool();

  // Add a string to the pool.  This returns a canonical permanent
  // pointer to the string.
  const char*
  add(const char*);

  const char*
  add(const std::string& s)
  { return this->add(s.c_str()); }

  // Add the prefix of a string to the pool.
  const char*
  add(const char *, size_t);

  // If a string is present, return the canonical string.  Otherwise,
  // return NULL.
  const char*
  find(const char*) const;

  // Turn the stringpool into an ELF strtab: determine the offsets of
  // all the strings.
  void
  set_string_offsets();

  // Get the offset of a string.
  off_t
  get_offset(const char*) const;

  off_t
  get_offset(const std::string& s) const
  { return this->get_offset(s.c_str()); }

  // Get the size of the ELF strtab.
  off_t
  get_strtab_size() const
  { return this->strtab_size_; }

  // Write the strtab into the output file at the specified offset.
  void
  write(Output_file*, off_t offset);

 private:
  Stringpool(const Stringpool&);
  Stringpool& operator=(const Stringpool&);

  // We store the actual data in a list of these buffers.
  struct Stringdata
  {
    // Length of data in buffer.
    size_t len;
    // Allocated size of buffer.
    size_t alc;
    // Buffer.
    char data[1];
  };

  // Copy a string into the buffers, returning a canonical string.
  const char*
  add_string(const char*);

  struct Stringpool_hash
  {
    size_t
    operator()(const char*) const;
  };

  struct Stringpool_eq
  {
    bool
    operator()(const char* p1, const char* p2) const
    { return strcmp(p1, p2) == 0; }
  };

  // Return whether s1 is a suffix of s2.
  static bool is_suffix(const char* s1, const char* s2);

  // The hash table is a map from string names to offsets.  We only
  // use the offsets if we turn this into an ELF strtab section.

#ifdef HAVE_TR1_UNORDERED_SET
  typedef Unordered_map<const char*, off_t, Stringpool_hash,
			Stringpool_eq,
			std::allocator<std::pair<const char* const, off_t> >,
			true> String_set_type;
#else
  typedef Unordered_map<const char*, off_t, Stringpool_hash,
			Stringpool_eq> String_set_type;
#endif

  // Comparison routine used when sorting into an ELF strtab.

  struct Stringpool_sort_comparison
  {
    bool
    operator()(String_set_type::iterator,
	       String_set_type::iterator) const;
  };

  String_set_type string_set_;
  std::list<Stringdata*> strings_;
  off_t strtab_size_;
};

} // End namespace gold.

#endif // !defined(GOLD_STRINGPOOL_H)
