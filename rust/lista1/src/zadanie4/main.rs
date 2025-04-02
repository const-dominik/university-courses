fn printer_error(s: &str) -> String {
    let mut errors = 0;
    let all = s.len() as i32;
    for c in s.chars() {
        if (c as u32) > 109 {
            errors += 1;
        }
    }
    let ret_str = format!("{}/{}", errors, all);
    return ret_str;
}

#[test]
fn printer() {
    assert_eq!(
        &printer_error("aaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbmmmmmmmmmmmmmmmmmmmxyz"),
        "3/56"
    );
    assert_eq!(
        &printer_error("kkkwwwaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbmmmmmmmmmmmmmmmmmmmxyz"),
        "6/60"
    );
    assert_eq!(
        &printer_error("kkkwwwaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbmmmmmmmmmmmmmmmmmmmxyzuuuuu"),
        "11/65"
    );
    assert_eq!(&printer_error("abcdeeffg"), "0/9");
    assert_eq!(&printer_error("n"), "1/1");
}
