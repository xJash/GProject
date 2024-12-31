// ============================================================================
// Data Structures For Game Programmers
// Ron Penton
// Array.h
// This is the basic 1D array class.
// ============================================================================
#ifndef _ARRAY_H_
#define _ARRAY_H_

#include <stdio.h>

template<class Datatype>
class Array
{

// -------------------------------------------------------
// Name:        Array::m_array
// Description: This is a pointer to the array.
// -------------------------------------------------------
    Datatype* m_Array;


// -------------------------------------------------------
// Name:        Array::m_size
// Description: the current size of the array.
// -------------------------------------------------------
    int m_Size;
	
public:

// -------------------------------------------------------
// Name:        Array
// Description: Array�� �޸𸮸� �Ҵ��Ѵ�.
// Arguments:   size - Array�� ũ��
// -------------------------------------------------------
    Array( int size )
    {
        // �迭�� ���� �޸𸮸� �Ҵ��Ѵ�.
        m_Array = new Datatype[size];

        // Array�� size�� �����Ѵ�.
        m_Size = size;
    }


// -------------------------------------------------------
// Name:        ~Array
// Description: Array�� �����Ѵ�.
// -------------------------------------------------------
    ~Array()
    {
		// Array�� �Ҵ�Ǿ� ������ �����Ѵ�.
        if( m_Array != 0 )
            delete[] m_Array;

        // Array Pointer�� �ʱ�ȭ�Ѵ�.
        m_Array = 0;
    }

// -------------------------------------------------------
//  Name:         operator[]
//  Description:  �־��� index�� Item�� �����ϵ��� �Ѵ�.
//  Arguments:    index - �迭�� Index
//  Return Value: index���� �迭�� ���� �ִ� Item�� Reference
// -------------------------------------------------------
    Datatype& operator[] ( int index )
    {
        return m_Array[index];
    }



// -------------------------------------------------------
//  Name:         Size
//  Description:  Array�� 
//  Arguments:    None.
//  Return Value: Array�� ũ�� 
// -------------------------------------------------------
    int Size()
    {
        return m_Size;
    }


// -------------------------------------------------------
//  Name:         operator DataType*
//  Description:  Array�� Pointer�� conver�ϴ� Operator
//  Arguments:    None.
//  Return Value: Array �� Pointer
// -------------------------------------------------------
    operator Datatype* ()
    {
        return m_Array;
    }


// -------------------------------------------------------
//  Name:         WriteFile
//  Description:  Array �� �����Ѵ�.
//  Arguments:    The Filename
//  Return Value: true on success, false on failure
// -------------------------------------------------------
    bool WriteFile( const char* pFileName )
    {
        FILE* fpOutFile = 0;
        int written = 0;

        // ������ ����.
        fpOutFile = _tfopen( pFileName, TEXT("wb") );

        // ���� ���⿡ �����ϸ� ���ư���.
        if( fpOutFile == 0 )	return false;

        // ���Ͽ� Array�� �����Ѵ�.
        written = fwrite( m_Array, sizeof( Datatype ), m_Size, fpOutFile );
        fclose( fpOutFile );

		// ���⿡ �������� ���ϸ� false
        if( written != m_Size )	return false;

        // ����
        return true;
    }
    

// -------------------------------------------------------
//  Name:         ReadFile
//  Description:  Array�� �о�´�.
//  Arguments:    The Filename
//  Return Value: true on success, false on failure
// -------------------------------------------------------
    bool ReadFile( const char* pFileName )
    {
        FILE* fpInFile = 0;
        int read = 0;

        // ������ ����.
        fpInFile = _tfopen( pFileName, TEXT("rb") );

        // ���� ���⿡ �����ϸ� ���ư���.
        if( fpInFile == 0 )		return false;

        // ���Ͽ� Array�� �о�´�.
        read = fread( m_Array, sizeof( Datatype ), m_Size, fpInFile );
        fclose( fpInFile );

		// �б⿡ �������� ���ϸ� false	
        if( read != m_Size )	return false;

        // ����
        return true;
    }


};




#endif