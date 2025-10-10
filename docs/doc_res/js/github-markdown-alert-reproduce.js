// Reproduce blockquote alert in GitHub Markdown
$('blockquote').each(function() {
    var $this = $(this);
    var $para0 = $this.find('p:first-child');
    var text = $para0.text().trim();

    // 检测是否包含提示类型
    var match = text.match(/^\[\!(NOTE|TIP|IMPORTANT|CAUTION|WARNING)\]/i);
    if (match) {
        var type = match[1].toLowerCase();

        // 添加样式类
        $this.addClass('markdown-alert ' + `markdown-alert-${type}`);
        $para0.addClass('markdown-alert-title');

        // 更新内容
        
    }
});
