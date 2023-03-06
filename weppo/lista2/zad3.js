const obj = {
    name: "adam",
    surname: "smith",
    nick: "",
    nickLogs: [],
    getAge() {
        return 21;
    },
    get fullName() {
        return `${this.name} ${this.surname}`;
    },
    set fullName(fullname) {
        const [name, surname] = fullname.split(" ");
        this.name = name;
        this.surname = surname;
    }
}

obj.nationality = "polish";
obj.sayHi = () => console.log("hi");
Object.defineProperty(obj, "nick", {
    get: function () { return this.nick },
    set: function (nick) { return this.nickLogs.push(nick) }
});
obj.nick = "dog";
console.log(obj);