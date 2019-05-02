function fibonacci(i)
    if(i == 0 ) then
        return 0
    elseif(i == 1) then 
        return 1
    else 
        return fibonacci(i - 1 ) + fibonacci( i - 2)
    end
    
end

for i = 1, 1000, 1 do
    print(fibonacci(20))
end