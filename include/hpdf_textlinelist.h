#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include "hpdf_types.h"
#include "hpdf_consts.h"

/**
 * The TextLine struct,
 * contains item and the pointers that point to previous TextLine/next TextLine.
 */
typedef struct TextLine {
    const char* item;
    HPDF_UINT len, num_rest;
    HPDF_BOOL LineBreak;
    HPDF_REAL rw;
    struct TextLine* next;
} TextLine;
/**
 * The LinkedList struct, contains the pointers that
 * point to first TextLine and last TextLine, the size of the LinkedList,
 * and the function pointers.
 */
typedef struct LinkedList {
    TextLine* head;
    TextLine* tail;
    // size of this LinkedList
    HPDF_UINT size;

    // add item after tail
    void (*Append) (struct LinkedList*, const char*, HPDF_UINT, HPDF_UINT, HPDF_REAL, HPDF_BOOL);

    // get first item
    TextLine* (*getFirst) (struct LinkedList*);

    // free allocated memory
    void (*Delete) (struct LinkedList*);

    // create a TextLine with item
    TextLine* (*createTextLine) (const char*, HPDF_UINT, HPDF_UINT, HPDF_REAL, HPDF_BOOL);
} LinkedList;

void Append (LinkedList* _this, const char *str, HPDF_UINT len, HPDF_UINT num_rest, HPDF_REAL rw, HPDF_BOOL LineBreak);
void Delete (LinkedList* _this);
LinkedList createLinkedList ();
TextLine* createTextLine (const char *str, HPDF_UINT len, HPDF_UINT num_rest, HPDF_REAL rw, HPDF_BOOL LineBreak);