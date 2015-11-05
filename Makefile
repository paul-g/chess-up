TMP_PATH="/tmp/spark_html_doc"
HTML_DIR="html"
TRASH=latex

update-doc: doc
	cp ${HTML_DIR} ${TMP_PATH} -R
	git fetch
	git checkout gh-pages
	cp ${TMP_PATH}/* . -R
	rm -rf ${TRASH}
	git add .
	git commit -m "Update documentation"
	git push -u origin gh-pages
	rm -rf ${TMP_PATH}

doc:
	doxygen docs/doxygen.conf

.PHONY: doc update-doc
