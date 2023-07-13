using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MergeSortCSharp
{
    /*
     * Merge Sort Algorithm:
     * Given an array, split the array into subarrays until they are a single element,
     * then as rememrge the single elements, sorting them as they are merged back into a single array
     */
    public class MergeSort
    {
   
        public static List<int> Sort(List<int> origList)
        {
            if(origList.Count > 1)
            {
                List<int> lhList = Split (origList);

                lhList = Sort(lhList);
                origList = Sort(origList);

                return Merge(lhList, origList);
            }
            return origList;
            
        }

        static List<int> Split(List<int> inList)
        {
            List<int> outList = new List<int>();
            int midPoint = inList.Count / 2;

            for(int i = 0; i < midPoint; i++)
            {
                outList.Add(inList[i]);
            }
            inList.RemoveRange(0, midPoint);

            return outList;
        }

        static List<int> Merge(List<int> lhList, List<int> rhList) 
        {
            int lIndex = 0;
            int rIndex = 0;

            List<int> mergedList= new List<int>();
            while(lIndex < lhList.Count && rIndex < rhList.Count) 
            {
                if (lhList[lIndex] < rhList[rIndex])
                {
                    mergedList.Add(lhList[lIndex]);
                    lIndex++;
                }
                else
                {
                    mergedList.Add(rhList[rIndex]);
                    rIndex++;
                }
            }

            for (; lIndex < lhList.Count; lIndex++)
            {
                mergedList.Add(lhList[lIndex]);
            }

            for(;rIndex < rhList.Count; rIndex++)
            {
                mergedList.Add(rhList[rIndex]);
            }

            return mergedList;
        }

    }
}
