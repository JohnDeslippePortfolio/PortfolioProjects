using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace QuickSortCSharp
{
    public class QuickSort
    {
        public static void Sort(List<int> userList)
        {
           QSort(userList, 0 ,userList.Count() - 1);

        }

        static void QSort(List<int> userList, int start, int end)
        {
            if(start >= end || start < 0)
            {
                return;
            }
            
            int currentPartition = Partition(userList, start, end);

            QSort(userList, currentPartition + 1, end);
            QSort(userList, start, currentPartition-1);
        }

        static void Swap(List<int> userList, int firstIndex, int secondIndex)
        {
            int temp = userList[firstIndex];
            userList[firstIndex] = userList[secondIndex];
            userList[secondIndex] = temp;
        }

        static int Partition(List<int> userList, int start, int end) 
        {
            int pivot = userList[end];
            int finalPivPosition = start - 1;

            for(int i = start; i < end; i++) 
            {
                if (userList[i] <= pivot)
                {
                    finalPivPosition++;
                    Swap(userList, i, finalPivPosition);
                }
            }

            finalPivPosition++;
            Swap(userList, finalPivPosition, end);
            return finalPivPosition;


        }
    }
}
