function createFs(n: number) { // tworzy tablicę n funkcji
    var fs: any[] = []; // i-ta funkcja z tablicy ma zwrócić i
    for (var i=0; i<n; i++) {
        fs[i] = (function(n) {
            return () => n;
        })(i)
    };
    return fs;
}
var myfs = createFs(10);
console.log( myfs[0]() ); // zerowa funkcja miała zwrócić 0
console.log( myfs[2]() ); // druga miała zwrócić 2
console.log( myfs[7]() );
// 10 10 10 // ale wszystkie zwracają 10!?