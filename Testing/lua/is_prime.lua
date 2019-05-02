require("math")

function isprime(n)

  for i = 2, n, 1 do
    if (math.fmod(n, i) == 0) then
        return false
    end
  end

  return true
end


function primes(n) 

  count = 0
  for i = 2, n, 1 do
  
    if (isprime(i)) then 
        count = count + 1
    end
  end

  return count
end

iterations = 1000

print(primes(iterations));