#!/usr/bin/env ruby

def binary_search(array, target) 
  p array
  esq = 0
  dir = array.length - 1

  while esq <= dir
    pivo = (esq + dir) / 2 
    guess = array[pivo]
      
    return true if guess == target

    if guess > target
      dir = pivo - 1
    else 
      esq = pivo + 1
    end
  end

  false
end

def order!(array) 
  (1...array.length).each do |i|
    key = array[i]
    j = i - 1

    while j >= 0 && array[j] > key 
      array[j + 1] = array[j]
      j -= 1
    end

    array[j + 1] = key
  end
end

list = [5, 3, 2, 1, 9]

order! list
