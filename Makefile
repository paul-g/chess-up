TMP_PATH="/tmp/spark_html_doc"

update-doc: doc
	cp html ${TMP_PATH} -R
	git fetch
	git checkout gh-pages
	cp ${TMP_PATH}/* . -R
	rm -rf latex
	git add .
	git commit -m "Update documentation"
	git push -u origin gh-pages
	rm -rf ${TMP_PATH}

doc:
	doxygen docs/doxygen.conf

.PHONY: doc update-doc
