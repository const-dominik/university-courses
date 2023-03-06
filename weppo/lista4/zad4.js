const stdin = process.openStdin();
stdin.addListener("data", d => {
    console.log(`Witaj, ${d.toString().trim()}!`);
    process.exit();
});