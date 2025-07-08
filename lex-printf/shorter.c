 /* *** teste 123 
/ teste */
 
 function particionar(array, low, high) {
      // elemento mais à direita como pivô
      pivo = array[high]


      // ponteiro para maior elemento
      i = low - 1
      for (int j : range(low, high)) {
          if array[j] <= pivo {
              i += 1
              temp = array[i]
              array[i] = array[j]
              array[j] = temp
          }
      }
   
      temp = array[i + 1]
      array[i + 1] = array[high]
      array[high] = temp
   
      return i + 1
   }
   
   function quickSort(array, low, high) {
      if low < high {
          pi = particionar(array, low, high)
          quickSort(array, low, pi - 1)
          quickSort(array, pi + 1, high)
      }
   }