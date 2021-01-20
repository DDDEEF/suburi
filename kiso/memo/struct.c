#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct student
{
  char name[20];
  int id;
  struct student* next;
} STUDENT;

STUDENT *head = NULL; //リストの先頭
STUDENT *tail = NULL; //リストの末尾

STUDENT *createNode(void);
void addNodeToList(void);
void printList(void);
void insertNodeToList(void);
void deleteNodeFromList(void);

int main(void)
{
  char input;
  char command;

  while(1)
  {
    printf("----------操作方法------------\n");
    printf("A:リストの末尾にノードを追加\n");
    printf("P:リスト内のノードをすべて表示\n");
    printf("I:リスト内の任意の場所にノードを挿入\n");
    printf("D:リスト内の任意のノードを削除します。\n");
    printf("コマンドを入力せよ:");

    scanf("%s", &input);
    command = toupper(input);

    switch(command)
    {
      case 'A':
        addNodeToList();
        break;
      case 'P':
        printList();
        break;
      case 'I':
        insertNodeToList();
        break;
      case 'D':
        deleteNodeFromList();
        break;
      default:
        printf("無効なコマンドです。\n");
        break;
    }
    printf(" \n");
  }
  return 0;
}

STUDENT* createNode(void)
{
  STUDENT* newNodePos;
  newNodePos = (STUDENT *)malloc(sizeof(STUDENT));

  return newNodePos;
}

void addNodeToList(void)
{
  STUDENT* newNodePos;
  int inputId;
  char inputName[20];

  newNodePos = createNode();

  printf("学籍番号を入力:");
  scanf("%d", &inputId);
  newNodePos->id = inputId;

  printf("名前を入力:");
  scanf("%s", inputName);
  strcpy(newNodePos->name, inputName);

  if((head == NULL) && (tail == NULL))
  {
    head = newNodePos;
    tail = newNodePos;
  }
  else
  {
    tail->next = newNodePos;
    tail = newNodePos;
  }

  tail->next = NULL;
  printf("ノードを追加しました。\n");
}

void printList(void)
{
  STUDENT *current;

  if((head == NULL) && (tail == NULL))
  {
    printf("リストは空です。\n");
    return;
  }

  current = head;
  printf("-------------------------------------\n");

  while(1)
  {
    printf("学籍番号:%d\n", current->id);
    printf("名前:%s\n", current->name);
    printf("自身のノードの場所:%d\n", current);
    printf("次のノードの場所:%d\n", current->next);
    printf("------------------------------------\n");

    if(current->next != NULL)
    {
      current = current->next;
    }
    else
    {
      printf("最後まで表示しました。\n");
      break;
    }
  }
}

void insertNodeToList(void)
{
  char insertTargetName[20] = "";
  STUDENT* current, *temp, *newNodePos;
  int inputId;
  char inputName[20];

  printf("挿入先のノードのnameを入力してください。\n");
  printf("入力されたnameを持つノードの後ろに、新しいノードを挿入します。\n");
  scanf("%s", insertTargetName);

  current = head;

  while(current != NULL)
  {
    if(strcmp(current->name, insertTargetName) == 0)
    {
      printf("ノードが見つかりました。\n");  
      break;
    }
    else
    {
      current = current->next;
    }
  }

  if(current == NULL){
    printf("ノードが見つかりませんでした。\n");
    return ;
  }

  newNodePos = createNode();

  printf("学籍番号を入力:");
  scanf("%d", &inputId);
  newNodePos->id = inputId;

  printf("名前を入力:");
  scanf("%s", inputName);
  strcpy(newNodePos->name, inputName);

  temp = current->next;

  current->next = newNodePos;

  newNodePos->next = temp;

  printf("ノードを挿入した。\n");
}

void deleteNodeFromList(void)
{
  char deleteTargetName[20] = "";
  STUDENT* current, *prev;

  printf("削除するノードのnameを入力してください。\n");
  scanf("%s", deleteTargetName);

  current = head;
  prev = NULL;

  while(current != NULL)
  {
    if(strcmp(current->name, deleteTargetName) == 0){
      printf("ノードが見つかりました。\n");
      break;
    }
    else
    {
      prev = current;
      current = current->next;
    }
  }

  if(current == NULL)
  {
    printf("ノードが見つからなかった\n");
    return;
  }

  if(current == head)
  {
    head = current->next;
    free(current);
  }
  else
  {
    prev->next = current->next;
    free(current);
  }
  printf("削除が完了しました。\n");
}
