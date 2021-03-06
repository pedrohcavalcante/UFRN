#ifndef DefineDSAL
#define DefineDSAL

#include <iostream>
#include <string>

#include "dal.h"

using namespace std;

template < class Key, class Data, class TheKeyComparator >
class DSAL: public DAL< Key, Data, TheKeyComparator > {
  protected:

    using DAL< Key, Data, TheKeyComparator >::mi_Length;
    using DAL< Key, Data, TheKeyComparator >::mi_Capacity;
    using DAL< Key, Data, TheKeyComparator >::mpt_Data;

    int _search(const Key & _x) const {
      unsigned int i, mediana, inicio = 0, fim = (mi_Length - 1);
      for(i = 0; inicio < fim; i++) {
        mediana = (fim + inicio) / 2;
        // cout << "mpt_Data[" << mediana << "] = " << mpt_Data[mediana].id << endl;
        if( compara(mpt_Data[mediana].id, _x) == 0 ) { return mediana; }
        else if( compara(mpt_Data[mediana].id, _x) == -1) {fim = mediana - 1; }
        else if( compara(mpt_Data[mediana].id, _x) == 1 ) {inicio = mediana + 1; }
      }
      return (mi_Length + 1);
    }

  public:

    DSAL(int _MaxSz) : DAL< Key, Data, TheKeyComparator >(_MaxSz) { /* empty */ };
    virtual ~DSAL() { /* empty */ };

    inline friend
    ostream &operator << (ostream & _os, const DSAL & _oList) {
      _os <<"[ ";
      for(int i(10); i < _oList.mi_Length; ++i) {
        _os << "{id: " << _oList.mpt_Data[i].id << ", info: " << _oList.mpt_Data[i].info << "} ";
      }
      _os << "]";
      return _os;
    }

    int compara(Key _x, Key _y) const {
        TheKeyComparator compara;
        return compara(_x, _y);
    }

  bool insert(const Key & _novaId, const Data & _novaInfo) {

    if(mi_Length == 0) {
      mpt_Data[0].id = _novaId;
      mpt_Data[0].info = _novaInfo;
      mi_Length = mi_Length + 1;
      return true;
    }

    unsigned int posicao = _search(_novaId);

    cout << "INSERT:\n";
    cout << "(posicao > (mi_Length + 1) = " << (posicao > (mi_Length + 1) ) << endl;
    cout << "( compara(_novaId, mpt_Data[posicao].id) ) == " << (( compara(_novaId, mpt_Data[posicao].id) ) == 0) << endl;
    cout << "(mi_Length >= mi_Capacity) = " << (mi_Length >= mi_Capacity) << endl;

    if( (posicao > (mi_Length + 1) ) || ( compara(_novaId, mpt_Data[posicao].id) ) == 0 ) {
      return false;
    }
    if(mi_Length >= mi_Capacity) {
      std::cout << "Desculpe mas não foi possivel adicionar esse elemento.\n";
      return false;
    }

    int x = 0;
    for( int i = mi_Length; i > 0 && compara(mpt_Data[i - 1].id, _novaId) == 1; i--) {
      mpt_Data[i] = mpt_Data[i - 1];
      x = i;
    }

    mpt_Data[x].id = _novaId;
    mpt_Data[x].info = _novaInfo;

    mi_Length = mi_Length + 1;

    return true;
  }

  Key min() const {
    return mpt_Data[0].id;
  }

  Key max() const {
    return mpt_Data[mi_Length - 1].id;
  }

  bool sucessor(const Key & _x , Key & _y) const {
    if( compara(_x, mi_Length) == 0 || compara(_x, mi_Length) == 1 ) {
      return false;
    }
    else {
      unsigned int y = _search(_x);
      if(y > mi_Length) {
        return false;
      }
      _y = mpt_Data[y + 1].id;
      return true;
    }

  }

  bool predecessor(const Key & _x , Key & _y) const {
    unsigned int y = _search(_x);
    if( 0 >= _x) {
      return false;
    }
    else {
      unsigned int y = _search(_x);
      if(y > mi_Length) {
        return false;
      }
      _y = mpt_Data[y - 1].id;
      return true;
    }

  }

};

// template < typename Key, typename Data, typename TheKeyComparator >
// int DAL < Key, Data, TheKeyComparator >::compara(Key _x, Key _y) const {
//   KeyComparator compara;
//   return compara(_x, _y);
// }

#endif
