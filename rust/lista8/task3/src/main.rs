fn main() {}

fn part_list(arr: Vec<&str>) -> String {
    let mut res = "".to_owned();
    for i in 0..arr.len() - 1 {
        res.push_str(
            format!(
                "({}, {})",
                arr[0..=i].join(" "),
                arr[i + 1..arr.len()].join(" ")
            )
            .as_str(),
        );
    }

    res
}

fn dotest(arr: Vec<&str>, exp: &str) -> () {
    println!("arr: {:?}", arr);
    let ans = part_list(arr);
    println!("actual:\n{}", ans);
    println!("expect:\n{}", exp);
    println!("{}", ans == exp);
    assert_eq!(ans, exp);
    println!("{}", "-");
}

#[test]
fn basis_tests() {
    dotest(vec!["I", "wish", "I", "hadn't", "come"],
            "(I, wish I hadn't come)(I wish, I hadn't come)(I wish I, hadn't come)(I wish I hadn't, come)");
    dotest(
        vec!["cdIw", "tzIy", "xDu", "rThG"],
        "(cdIw, tzIy xDu rThG)(cdIw tzIy, xDu rThG)(cdIw tzIy xDu, rThG)",
    );
    dotest(vec!["a", "b"], "(a, b)");
    dotest(
        vec!["cdIw", "tzIy", "xDu"],
        "(cdIw, tzIy xDu)(cdIw tzIy, xDu)",
    );
    dotest(
        vec!["test1", "test2", "a"],
        "(test1, test2 a)(test1 test2, a)",
    );
}
