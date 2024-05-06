#include "hpdf_textlinelist.h"
/** add item to tail
 */
void Append (LinkedList* _this, const char *str, HPDF_UINT len, HPDF_UINT num_rest, HPDF_REAL rw, HPDF_BOOL LineBreak) {
    TextLine* newTextLine = _this->createTextLine(str, len, num_rest, rw, LineBreak);
    TextLine* head = _this->head;
    TextLine* tail = _this->tail;
    // list is empty
    if (head == NULL)
        _this->head = newTextLine;
    else { // has item(s)
        TextLine* lastTextLine = tail;
        if (tail == NULL) // only head TextLine
            lastTextLine = head;
        lastTextLine->next = newTextLine;
        _this->tail = newTextLine;
    }
    _this->size++;
}
/** get item from head
 */
TextLine* getFirst (LinkedList* _this) {
    return _this->head;
}
/** free allocated memory
 */
void Delete (LinkedList* _this) {
    TextLine* tmp;
    TextLine* textline = _this->head;
    while( textline != NULL)
    {
        tmp = textline->next;
        free(textline);
        textline = tmp;
    }
}
/** create a LinkedList
 */
LinkedList createLinkedList () {
    LinkedList list;
    list.head = NULL;
    list.tail = NULL;
    list.size = 0;
    list.Append = &Append;
    list.getFirst = &getFirst;
    list.createTextLine = &createTextLine;
    list.Delete = &Delete;
    return list;
}
/** create a TextLine
 */
TextLine* createTextLine (const char *str, HPDF_UINT len, HPDF_UINT num_rest, HPDF_REAL rw, HPDF_BOOL LineBreak) {
    TextLine* textline = (TextLine*) malloc (sizeof(TextLine));
    textline->item = str;
    textline->len = len;
    textline->num_rest = num_rest;
    textline->rw = rw;
    textline->LineBreak = LineBreak;
    textline->next = NULL;
    return textline;
}