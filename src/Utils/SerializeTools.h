#ifndef SERIALIZETOOL_H
#define SERIALIZETOOL_H

char *SERIALIZE_Int_Str(int a);
char *SERIALIZE_Float_Str(float a);
char *SERIALIZE_Char_Str(char a);
char *SERIALIZE_Fkey_Str(TPForeignKey *a);

#endif