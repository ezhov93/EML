/*
 * @file   eeprom.h
 * @author Mikhail Ezhov <ezhov93@gmail.com>
 * @brief  EEPROM class.
 */
 

#ifndef EEPROM_H
#define EEPROM_H

#include <ecore.h>

class Eeprom
{
public:
  enum Helper: uint32 {
    NumberDWordOfPages = 1024,
    PageSize = NumberDWordOfPages*sizeof(uint32),
    NumberPagesOfMainBank = 32,
    NumberPagesOfInfoBank = 1,
    PageMask = 0x1F000,
    PageEmpty = 0xFFFFFFFF
  };

  enum Bank { MainBank, InfoBank , AllBanks	};  
  enum Page  {
    Page0, 
    Page1, 
    Page2,
    Page3,
    Page4,
    Page5,
    Page6,
    Page7,
    Page8,
    Page9,    
    Page10,
    Page11,
    Page12,
    Page13,
    Page14,
    Page15,
    Page16,
    Page17,
    Page18,
    Page19, 
    Page20,
    Page21,
    Page22,
    Page23,
    Page24, 
    Page25,
    Page26,
    Page27,
    Page28,
    Page29,
    Page30,
    Page31
  };  
  
	explicit Eeprom(Bank blank = InfoBank);
  void begin();
	void begin(Bank blank);
  Bank bank() const;
  void setBank(Bank bank);
	void format(void);  
	void erase(Page page);
  bool isEmpty() const;
  bool isEmpty(Page page) const;
  
  uint32 read (uint32 address) const;
  void read (uint32 address, void* data, int size);
  
  void write(uint32 address, uint32 data);
  void write(uint32 address, void* data, int size);
  /*
	void update(uint32 address, uint32 data);
  void update(uint32 address, void* data, int size);
  */
  static uint32 pageToAddress(Page page);
  static Page addressToPage(uint32 address);
  
private:
  Bank _bank;
};

#endif	// EEPROM_H

