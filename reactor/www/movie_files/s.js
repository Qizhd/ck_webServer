function addFavorite(url,title){try{window.external.addFavorite(url,title)}catch(e){try{window.sidebar.addPanel(title,url,'')}catch(e){alert("加入收藏失败，请使用Ctrl+D进行添加!")}}};function ckSearch(){var kw=document.sform.q.value;if(kw==""||kw=="影片名/ 明星/ 导演/ 地区/ 年代/ imdb"||kw.length<2){document.sform.q.value="";document.sform.q.className='si';document.sform.q.focus();return false}}function isIE(){if(window.navigator.userAgent.toLowerCase().indexOf("msie")>=1)return true;else return false}if(!isIE()){HTMLElement.prototype.__defineGetter__("innerText",function(){var anyString="";var childS=this.childNodes;for(var i=0;i<childS.length;i++){if(childS[i].nodeType==1)anyString+=childS[i].tagName=="BR"?'\n':childS[i].innerText;else if(childS[i].nodeType==3)anyString+=childS[i].nodeValue}return anyString});HTMLElement.prototype.__defineSetter__("innerText",function(sText){this.textContent=sText})}function changeS(obj){var text=obj.innerText;if(text=='站内'){obj.innerText='baidu';document.getElementById('cst').innerText='站内';document.sform.action='https://www.jsr9.com/';}else{obj.innerText='站内';document.getElementById('cst').innerText='baidu';document.sform.action='http://zhannei.baidu.com/cse/search';document.getElementById('keyword').name='q';document.getElementById('search').name='s';document.getElementById('form').target='_blank';}obj.parentNode.parentNode.className='Ts spe'}function switchTab(on,off){document.getElementById(on).style.display="block";document.getElementById('t_'+on).className="able this";document.getElementById(off).style.display="none";document.getElementById('t_'+off).className="able"}