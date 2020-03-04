#ifndef __ABSLL_H__
#define __ABSLL_H__

typedef enum {false,true} bool;

typedef struct ABSLL* PABSLL;

typedef void (*DESTROY_OBJECT)(void*);

typedef void (*MANIPULATE_OBJECT)(void*);

typedef int (*COMPARE_OBJECT)(void*, void*);

/*
 *  创建列表，返回一个抽象列表指针
 */
PABSLL ll_create();

/*
 *  释放列表
 *  参数1：列表指针
 *  参数2：回调函数，用于释放列表元素
 *  void (*DESTROY_OBJECT)(void*);
 */
void ll_destroy(PABSLL, DESTROY_OBJECT);

/*
 *  向列表追加元素
 *  参数1：列表指针
 *  参数2：列表元素指针
 */
void ll_append(PABSLL, void*);

/*
 *  向列表插入元素
 *  参数1：列表指针
 *  参数2：插入位置
 *  参数3：列表元素指针
 */
void ll_insert(PABSLL, unsigned int, void*);

/*
 *  删除列表元素
 *  参数1：列表指针
 *  参数2：删除元素位置
 *  参数3：回调函数，用于释放列表元素
 *  void (*DESTROY_OBJECT)(void*);
 */
void ll_delete(PABSLL, unsigned int, DESTROY_OBJECT);

/*
 *  清空列表
 *  参数1：列表指针
 *  参数2：回调函数，用于释放列表元素
 *  void (*DESTROY_OBJECT)(void*);
 */
void ll_clear(PABSLL, DESTROY_OBJECT);

/*
 *  遍历列表
 *  参数1：列表指针
 *  参数2：回调函数，对列表元素的操作
 *  void (*MANIPULATE_OBJECT)(void*);
 */
void ll_traverse(PABSLL, MANIPULATE_OBJECT);

/*
 *  判断元素是否在列表中，返回bool值
 *  参数1：列表指针
 *  参数2：列表元素
 *  参数3：回调函数，用作列表元素间比较
 *  int (*COMPARE_OBJECT)(void*, void*);返回0 1 -1
 */
bool ll_search(PABSLL, void*, COMPARE_OBJECT);

/*
 *  获取列表长度，返回非负整数值
 *  参数1：列表指针
 */
unsigned int ll_get_length(PABSLL);

/*
 *  列表判空，返回bool值
 *  参数1：列表指针
 */
bool ll_is_empty(PABSLL);

#endif